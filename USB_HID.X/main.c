

/*
 * File:   main.c
 * Author: kolel
 *
 * Created on 25 November 2022, 5:48 PM
 */

#include "system.h"
#include "usb_device.h"
#include <xc.h>
#include <stdbool.h>
#include "usb_start.h"
#include "GenericTypeDefs.h"
#include "usb_function_hid.h"
#include "usb_device.h"
#include "usb_hal_pic18.h"
#include "uart.h"
#include <stdio.h>
static void gpioInitialize(void);
static void Interrupt_Init(void);
static void timerStop(void);
static void Interrupt_Init(void);
static void Enable_Interrupt(void);
static void timerZero_Init(void);
static void timerStart(void);
static void timer1_Init(void);

//#define TIMER_RELOAD    50535u // wait 10 milliseconds... 

#define TIMER_RELOAD    64037u
#define _XTAL_FREQ      48000000
#define SW_IS_LOW       !PORTAbits.RA4
#define SW_IS_HIGH      PORTAbits.RA4
#define PUSH_BUTTON     PORTAbits.RA4

uint8_t pushButtonCount = 0; 


enum usbState {
    INITIALIZATION = 0, 
    USB_RUN, 
    IDLE
};
enum usbState usbTimerState = INITIALIZATION;

static void InitializeSystem(void);
void UserInit(void);
void USBCBInitEP(void);
void USBCBStdSetDscHandler(void);
void USBCBCheckOtherReq(void);
void USBCBErrorHandler(void);
void USBCB_SOF_Handler(void);
void USBCBWakeFromSuspend(void);
void USBCBSuspend(void);

/** VARIABLES ******************************************************/

volatile bool runFlag = false;
#define FIXED_ADDRESS_MEMORY true
#define HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS  __at (0x500)
#define HID_CUSTOM_IN_DATA_BUFFER_ADDRESS   __at (0x600)
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata HID_CUSTOM_OUT_DATA_BUFFER = HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS
        unsigned char ReceivedDataBuffer[64];
        #pragma udata HID_CUSTOM_IN_DATA_BUFFER = HID_CUSTOM_IN_DATA_BUFFER_ADDRESS
        unsigned char ToSendDataBuffer[64];
        #pragma udata

    #elif defined(__XC8)
        unsigned char ReceivedDataBuffer[64] HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
        unsigned char ToSendDataBuffer[64] HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;
    #endif
#else
    unsigned char ReceivedDataBuffer[64];
    unsigned char ToSendDataBuffer[64];
#endif

volatile USB_HANDLE USBOutHandle;    
volatile USB_HANDLE USBInHandle;

void __interrupt(high_priority) myISR_high(void) {
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {

        TMR1H = (uint8_t) (TIMER_RELOAD >> 8);
        TMR1L = (TIMER_RELOAD & 0xFF);
        PIR1bits.TMR1IF = 0;
        switch (usbTimerState) {
            case IDLE:
            {

            }
                break;

            case INITIALIZATION:
            {

            }
                break;

            case USB_RUN:
            {
#if  USB_FUNCTION
                USBDeviceTasks(); //run this every 1 milliseconds...
                LATEbits.LATE2 ^= 1;
#endif
            }
                break;

            default:
            {

            }
                break; // 
        }
    }

    if (PIE1bits.RC1IE && PIR1bits.RC1IF) {
        UART_rx_complete_irq();
    }//end if for UART receive reception
    if (PIE1bits.TX1IE && PIR1bits.TX1IF) {
        UART_tx_udr_empty_irq();
    }
}//end of interrupt

void __interrupt(low_priority) myISR_low(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        TMR0H = 0xC2;
        TMR0L = 0xF7;
        LATAbits.LA1 ^= 1;
        runFlag = true;
        INTCONbits.TMR0IF = 0;
    }//end of interrupt routine for timer


}

void main(void) {

    gpioInitialize();

    timerZero_Init();

    Interrupt_Init();

    timerStart();

    timer1_Init();

    Enable_Interrupt(); //enable global and peripheral interrupts... 


#if defined(USB_FUNCTION)
    InitializeSystem();
    di();
    usbTimerState = USB_RUN; // change it to run mode... 
    ei();
#endif

    UART_Init(115200);

    UART_putrs("Hello World\r\n");

    while (1) 
    {
        CLRWDT();
        if(PUSH_BUTTON == false)
        {
            __delay_ms(20);
            if(PUSH_BUTTON == false)
            {
                while(PUSH_BUTTON == false); 
                RESET();      
            }
        }else
        {
            pushButtonCount = 0; 
        }
#if defined(USB_FUNCTION)
        if (USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended() == true) 
        {
            //Do nothing.... 
        } else {

            if (!HIDTxHandleBusy(USBInHandle) && runFlag == true) 
            {
                for (uint8_t cnt = 0; cnt < 64; cnt++) 
                {
                    ToSendDataBuffer[cnt] = '@';
                }

                USBInHandle = HIDTxPacket(HID_EP, (uint8_t*) &ToSendDataBuffer[0], 64);
                
                if(USBInHandle == 0)
                {
                    UART_putrs("It is zero brother...\r\n");
                }
                runFlag = false;
                UART_putrs("Hello World from PIC18\r\n");
            }

            //if (runFlag == true) {
                //runFlag = false;
                //UART_putrs("Hello World\r\n");
            //}
                        
            if (!HIDRxHandleBusy(USBOutHandle)) //Check if data was received from the host.
            {
                switch (ReceivedDataBuffer[0]) //Look at the data the host sent, to see what kind of application specific command it sent.
                {
                    case 0x80: //mTouch callibration command
                    {
                        UART_putrs("mTouch callibration command");
                        
                    }
                        break;

                    case 0x20:
                    {
                        uint16_t potVoltage;
                        UART_putrs("Read ADC Voltage");
                        if (!HIDTxHandleBusy(USBInHandle)) {
                            /* Select ADC channel */
                            ADCON0bits.CHS = 4;

                            /* Make sure A/D interrupt is not set */
                            PIR1bits.ADIF = 0;

                            /* Begin A/D conversion */
                            ADCON0bits.GO = 1;
                            //Wait for A/D convert complete
                            while (!PIR1bits.ADIF);

                            /* Get the value from the A/D */
                            potVoltage = ADRES;

                            ToSendDataBuffer[0] = 0x20;
                            ToSendDataBuffer[1] = (BYTE) (potVoltage);
                            ToSendDataBuffer[2] = (BYTE) (potVoltage >> 8);

                            USBInHandle = HIDTxPacket(HID_EP, (BYTE*) & ToSendDataBuffer[0], 64);
                        }
                    }
                        break;

                    case 0x30:
                    {
                        uint16_t w;
                        UART_putrs("Read Button Brother 1....");
                        if (!HIDTxHandleBusy(USBInHandle)) {
                            //w = mTouchReadButton(0);

                            ToSendDataBuffer[0] = 0x30;
                            ToSendDataBuffer[1] = (BYTE) w;
                            ToSendDataBuffer[2] = (BYTE) (w >> 8);

                            USBInHandle = HIDTxPacket(HID_EP, (BYTE*) & ToSendDataBuffer[0], 64);
                        }
                    }
                        break;

                    case 0x31:
                    {
                        uint16_t w;
                        UART_putrs("Read Button Brother 2....");
                        if (!HIDTxHandleBusy(USBInHandle)) {
                            //w = mTouchReadButton(1);

                            ToSendDataBuffer[0] = 0x31;
                            ToSendDataBuffer[1] = (BYTE) w;
                            ToSendDataBuffer[2] = (BYTE) (w >> 8);

                            USBInHandle = HIDTxPacket(HID_EP, (BYTE*) & ToSendDataBuffer[0], 64);
                        }
                    }
                        break;

                    case 0x32:
                    {
                        uint16_t w;
                        UART_putrs("Read Button Brother 3....");
                        if (!HIDTxHandleBusy(USBInHandle)) 
                        {
                            //w = mTouchReadButton(2);

                            ToSendDataBuffer[0] = 0x32;
                            ToSendDataBuffer[1] = (BYTE) w;
                            ToSendDataBuffer[2] = (BYTE) (w >> 8);

                            USBInHandle = HIDTxPacket(HID_EP, (BYTE*) & ToSendDataBuffer[0], 64);
                        }
                    }
                        break;

                    case 0x33:
                    {
                        uint16_t w;
                        UART_putrs("Read Button Brother 4....");
                        if (!HIDTxHandleBusy(USBInHandle)) {
                            //w = mTouchReadButton(3);

                            ToSendDataBuffer[0] = 0x33;
                            ToSendDataBuffer[1] = (BYTE) w;
                            ToSendDataBuffer[2] = (BYTE) (w >> 8);

                            USBInHandle = HIDTxPacket(HID_EP, (BYTE*) & ToSendDataBuffer[0], 64);
                        }
                    }
                        break;

                    case 0x40:
                    {
                        //                  BMA150_REG regX_MSB;
                        //                  BMA150_REG regX_LSB;
                        UART_putrs("BMA150_REG regX_MSB...");
                        if (!HIDTxHandleBusy(USBInHandle)) {

                            ToSendDataBuffer[0] = 0x40;
                            ToSendDataBuffer[1] = (BYTE) 0; //(regX_LSB.val>>6);
                            ToSendDataBuffer[2] = (BYTE) 1; //(regX_MSB.val);

                            USBInHandle = HIDTxPacket(HID_EP, (BYTE*) & ToSendDataBuffer[0], 64);
                        }
                    }
                        break;

                    case 0x41:
                    {
                        //                  BMA150_REG regY_MSB;
                        //                 BMA150_REG regY_LSB;
                        UART_putrs("BMA150_REG regY_MSB...");
                        if (!HIDTxHandleBusy(USBInHandle)) {
                            //regY_LSB.val = BMA150_ReadByte(BMA150_ACC_Y_LSB);
                            //regY_MSB.val = BMA150_ReadByte(BMA150_ACC_Y_MSB);

                            ToSendDataBuffer[0] = 0x41;
                            ToSendDataBuffer[1] = (BYTE) 0; //(regY_LSB.val>>6);
                            ToSendDataBuffer[2] = (BYTE) 1; //(regY_MSB.val);

                            USBInHandle = HIDTxPacket(HID_EP, (BYTE*) & ToSendDataBuffer[0], 64);
                        }
                    }
                        break;

                    case 0x42:
                    {
                        //                  BMA150_REG regZ_MSB;
                        //                  BMA150_REG regZ_LSB;
                        UART_putrs("BMA150_REG regZ_MSB...");
                        if (!HIDTxHandleBusy(USBInHandle)) {
                            ////regZ_LSB.val = BMA150_ReadByte(BMA150_ACC_Z_LSB);
                            //regZ_MSB.val = BMA150_ReadByte(BMA150_ACC_Z_MSB);

                            ToSendDataBuffer[0] = 0x42;
                            ToSendDataBuffer[1] = (BYTE) 6; //(regZ_LSB.val>>6);
                            ToSendDataBuffer[2] = (BYTE) 8; //(regZ_MSB.val);
                            USBInHandle = HIDTxPacket(HID_EP, (BYTE*) & ToSendDataBuffer[0], 64);
                        }
                    }
                        break;

                    case 0x43:
                    {
                        //BMA150_REG regT_MSB;
                        UART_putrs("BMA150_REG regT_MSB...");
                        if (!HIDTxHandleBusy(USBInHandle)) 
                        {
                            //regT_MSB.val = BMA150_ReadByte(BMA150_TEMP);

                            ToSendDataBuffer[0] = 0x43;
                            ToSendDataBuffer[1] = (BYTE) 5; //regT_MSB.val;
                            USBInHandle = HIDTxPacket(HID_EP, (BYTE*) & ToSendDataBuffer[0], 64);
                        }
                    }
                        break;

                    default:
                    {
                        UART_putrs("Invalid...\r\n");
                        char temp[100];
                        uint8_t cnt;
                        for (cnt = 0; cnt < 64; cnt++) {

                            sprintf(temp, "cnt %u is %u\r\n", cnt, ReceivedDataBuffer[cnt]);
                            UART_puts(temp);
                        }

                    }
                    break;

                }
                //Re-arm the OUT endpoint for the next packet
                USBOutHandle = HIDRxPacket(HID_EP, (BYTE*) & ReceivedDataBuffer, 64);
            }
        }
    }
#endif
    return;
}

static void gpioInitialize(void) {
    ADCON1 |= 0x0F;
    TRISAbits.RA1 = 0;
    LATAbits.LA1 = 0;
    
    TRISAbits.RA4 = 1;
    TRISEbits.TRISE2 = 0; // 
    

}

static void Interrupt_Init(void) {
    INTCONbits.GIE = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    INTCONbits.PEIE = 1; //enable peripheral interrupt
    INTCONbits.PEIE_GIEL = 1;
    RCONbits.IPEN = 1;
}

static void timerZero_Init(void) {
    TMR0H = 0xC2;
    TMR0L = 0xF7;
    T0CON = 0b10000111;
    INTCON2bits.TMR0IP = 0;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
}

static void timer1_Init(void) {
    TMR1H = (uint8_t) (TIMER_RELOAD >> 8);
    TMR1L = (TIMER_RELOAD & 0xFF);
    T1CON = 0b10110001;

    IPR1bits.TMR1IP = 1; //high priority... 
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
}

static void Enable_Interrupt(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}//end enable interrupt

static void timerStart(void) {
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON = 1;
    INTCONbits.TMR0IE = 1;
}

static void timerStop(void) {
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 0;
}

void USBCBInitEP(void) {
    //enable the HID endpoint
    USBEnableEndpoint(HID_EP, USB_IN_ENABLED | USB_OUT_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);
    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = (volatile USB_HANDLE) HIDRxPacket(HID_EP, (uint8_t *) & ReceivedDataBuffer, 64);
}

void UserInit(void) {
    //initialize the variable holding the handle for the last
    // transmission
    USBOutHandle = 0;
    USBInHandle = 0;
}//end UserInit

static void InitializeSystem(void) {

    USBDeviceInit(); //usb_device.c.  Initializes USB module SFRs and firmware
    //variables to known states.
    UserInit();

}//end InitializeSystem

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size) {
    switch (event) {
        case EVENT_CONFIGURED:
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();

            break;
        default:
            break;
    }
    return TRUE;
}

void USBCBStdSetDscHandler(void) {
    // Must claim session ownership if supporting this request
}//end

void USBCBCheckOtherReq(void) 
{
    USBCheckHIDRequest();
}//end

void USBCBErrorHandler(void) 
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

    // Typically, user firmware does not need to do anything special
    // if a USB error occurs.  For example, if the host sends an OUT
    // packet to your device, but the packet gets corrupted (ex:
    // because of a bad connection, or the user unplugs the
    // USB cable during the transmission) this will typically set
    // one or more USB error interrupt flags.  Nothing specific
    // needs to be done however, since the SIE will automatically
    // send a "NAK" packet to the host.  In response to this, the
    // host will normally retry to send the packet again, and no
    // data loss occurs.  The system will typically recover
    // automatically, without the need for application firmware
    // intervention.

    // Nevertheless, this callback function is provided, such as
    // for debugging purposes.
}

void USBCB_SOF_Handler(void) 
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

void USBCBWakeFromSuspend(void) {
    //while(AppPowerReady() == FALSE)
    //{
    // Soft Start the APP_VDD	
    //}
}

void USBCBSuspend(void) {
    //Turn off the App Vdd
    //AppPowerDisable();
}