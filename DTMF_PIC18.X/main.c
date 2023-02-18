/*
 * File:   MAIN.c
 * Author: kolel
 *
 * Created on 06 February 2023, 8:31 PM
 */


#include <xc.h>
#include "main.h"
#include "I2C.h"
#include "SSD1306.h"
#include "keypad.h"
static void gpioInitialize(void);
static void Interrupt_Init(void);
static void timerStop(void);
static void Interrupt_Init(void);
static void Enable_Interrupt(void);
static void timerZero_Init(void);
static void timerStart(void);
static void timer1_Init(void);
static void timer3Init(void);

#define _XTAL_FREQ  48000000UL
#define GET_HIGH_BYTE(value)    (uint8_t) (value >> 8)
#define GET_LOW_BYTE(value)     (uint8_t) (value & 0xFF) 

// DTMF LOW FREQUENCIES... 
#define FREQ_697_VALUE          64466
#define FREQ_770_VALUE          64562
#define FREQ_852_VALUE          64656
#define FREQ_941_VALUE          64739  

#define FREQ_1209_VALUE         64915 // 1240
#define FREQ_1336_VALUE         64974
#define FREQ_1477_VALUE         65028
#define FREQ_1633_VALUE         65076

#define TIMER0_VALUE            60848 // 

typedef enum {
    FREQ_1209 = 0,
    FREQ_1336,
    FREQ_1477,
    FREQ_1633,
    FREQ_HIGH_NONE,
} highFrequency;

typedef enum {
    FREQ_697 = 0,
    FREQ_770,
    FREQ_852,
    FREQ_941,
    FREQ_LOW_NONE,
} lowFrequency;

typedef enum {
    RUN = 0,
    RUNNING,
    IDLE,
} dtmfStateMachine;

volatile dtmfStateMachine mydtmfStateMachine = IDLE;
volatile highFrequency myHighFrequency = FREQ_HIGH_NONE;
volatile lowFrequency myLowFrequency = FREQ_LOW_NONE;

#define HIGH_FREQ_PIN_LOW()     LATEbits.LATE0 = 0
#define HIGH_FREQ_PIN_HIGH()    LATEbits.LATE0 = 1

#define LOW_FREQ_PIN_LOW()      LATEbits.LATE2 = 0
#define LOW_FREQ_PIN_HIGH()     LATEbits.LATE2 = 1

#define HIGH_TIMER_ON()         T3CONbits.TMR3ON = 1
#define HIGH_TIMER_OFF()        T3CONbits.TMR3ON = 0

#define LOW_TIMER_ON()          T1CONbits.TMR1ON = 1
#define LOW_TIMER_OFF()         T1CONbits.TMR1ON = 0
void loadLowTimer(lowFrequency value);
void loadHighTimer(highFrequency value);

void __interrupt(high_priority) myISR_high(void) {
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        switch (myLowFrequency) {
            case FREQ_697:
            {
                LATEbits.LATE2 ^= 1;
                TMR1H = GET_HIGH_BYTE(FREQ_697_VALUE);
                TMR1L = GET_LOW_BYTE(FREQ_697_VALUE);
            }
                break;
            case FREQ_770:
            {
                LATEbits.LATE2 ^= 1;
                TMR1H = GET_HIGH_BYTE(FREQ_770_VALUE);
                TMR1L = GET_LOW_BYTE(FREQ_770_VALUE);

            }
                break;

            case FREQ_852:
            {
                LATEbits.LATE2 ^= 1;
                TMR1H = GET_HIGH_BYTE(FREQ_852_VALUE);
                TMR1L = GET_LOW_BYTE(FREQ_852_VALUE);
            }
                break;

            case FREQ_941:
            {
                LATEbits.LATE2 ^= 1;
                TMR1H = GET_HIGH_BYTE(FREQ_941_VALUE);
                TMR1L = GET_LOW_BYTE(FREQ_941_VALUE);
            }
                break;
            case FREQ_LOW_NONE:
            {
                LOW_TIMER_OFF();
            }
            default:
            {

            }
                break;
        }

    }

    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        //Reload... 65 ms... 

        //LATAbits.LATA5 ^= 1; 
        LATAbits.LA1 ^= 1;


        switch (mydtmfStateMachine) {
            case RUN:
            {
                HIGH_TIMER_ON(); //TURN HIGH TIMER ON ... 
                LOW_TIMER_ON(); //TURN LOW TIMER ON ... 
                mydtmfStateMachine = RUNNING;
            }
                break;

            case RUNNING:
            {
                //Turn High Freq PI low
                HIGH_FREQ_PIN_LOW();
                //Turn Low Freq PIN LOW
                LOW_FREQ_PIN_LOW();

                myHighFrequency = FREQ_HIGH_NONE;
                myLowFrequency = FREQ_LOW_NONE;
                //Stop timer high frquency..
                HIGH_TIMER_OFF();
                //Stop timer low frequency... 
                LOW_TIMER_OFF();
                //change value to IDLE

                mydtmfStateMachine = IDLE;
            }
                break;

            case IDLE:
            {

                //Do nothing... 
            }
                break;

            default:
            {

            }
        }

        TMR0H = GET_HIGH_BYTE(TIMER0_VALUE);
        TMR0L = GET_LOW_BYTE(TIMER0_VALUE);
        INTCONbits.TMR0IF = 0;

    }
    if (PIE1bits.RC1IE && PIR1bits.RC1IF) {
        //UART_rx_complete_irq();
    }//end if for UART receive reception
    if (PIE1bits.TX1IE && PIR1bits.TX1IF) {
        //UART_tx_udr_empty_irq();
    }
}//end of interrupt

void __interrupt(low_priority) myISR_Low(void) {
    if (PIE2bits.TMR3IE && PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        switch (myHighFrequency) {
            case FREQ_1209:
            {
                LATEbits.LATE0 ^= 1;
                TMR3H = GET_HIGH_BYTE(FREQ_1209_VALUE);
                TMR3L = GET_LOW_BYTE(FREQ_1209_VALUE);
            }
                break;

            case FREQ_1336:
            {
                LATEbits.LATE0 ^= 1;
                TMR3H = GET_HIGH_BYTE(FREQ_1336_VALUE);
                TMR3L = GET_LOW_BYTE(FREQ_1336_VALUE);
            }
                break;

            case FREQ_1477:
            {
                LATEbits.LATE0 ^= 1;
                TMR3H = GET_HIGH_BYTE(FREQ_1477_VALUE);
                TMR3L = GET_LOW_BYTE(FREQ_1477_VALUE);
            }
                break;

            case FREQ_1633:
            {
                LATEbits.LATE0 ^= 1;
                TMR3H = GET_HIGH_BYTE(FREQ_1633_VALUE);
                TMR3L = GET_LOW_BYTE(FREQ_1633_VALUE);
            }
                break;

            case FREQ_HIGH_NONE:
            {
                HIGH_TIMER_OFF();
            }
                break;

            default:
            {

            }
                break;
        }
    }
}

void main(void) 
{
    gpioInitialize();
    timer1_Init();
    timerZero_Init();
    Interrupt_Init();
    Enable_Interrupt();
    timer3Init();
    Keypad_Init(); //initialize the keypad... 
    I2C_INTIALIZE(400000);

    __delay_ms(100);
    
    SSD1306_Init(); // initialise
    SSD1306_GotoXY(0, 0);
    
    SSD1306_Clear();
    SSD1306_Puts("Fey-Tech", &Font_7x10, 1);
    SSD1306_GotoXY(0, 10);
    SSD1306_Puts("Designer:", &Font_7x10, 1);
    SSD1306_GotoXY(0, 20);
    SSD1306_Puts("www.feytech.co.za", &Font_7x10, 1); 
    SSD1306_GotoXY(0, 30);
    SSD1306_Puts("Nestor Kalambay", &Font_7x10, 1); 
    SSD1306_UpdateScreen(); //display
    
    for(uint8_t i = 0; i < 3; i++)
    {
        __delay_ms(1000);
    }
    SSD1306_Clear();
    
    SSD1306_GotoXY(0, 0);
    SSD1306_Putc('@', &Font_7x10, 1); 
    SSD1306_UpdateScreen(); //display
    while (1) 
    {
        volatile int8_t keypadValue = Keypad_Sample(); 
        if(keypadValue != -1)
        {
            SSD1306_GotoXY(0, 0);
            SSD1306_Putc((char ) keypadValue, &Font_7x10, 1); 
            SSD1306_UpdateScreen(); //display
            
            // Process pressed key... 
            
            switch(keypadValue)
            {
                case '1':
                {
                    di(); 
                    loadLowTimer(FREQ_697);

                    loadHighTimer(FREQ_1209);

                    myLowFrequency = FREQ_697;

                    myHighFrequency = FREQ_1209;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break; 
                
                case '2':
                {
                    di(); 
                    loadLowTimer(FREQ_697);

                    loadHighTimer(FREQ_1336);

                    myLowFrequency = FREQ_697;

                    myHighFrequency = FREQ_1336;

                    mydtmfStateMachine = RUN;
                    ei();
                }break;
                
                case '3':
                {
                    di(); 
                    loadLowTimer(FREQ_697);

                    loadHighTimer(FREQ_1477);

                    myLowFrequency = FREQ_697;

                    myHighFrequency = FREQ_1477;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case '4':
                {
                    di(); 
                    loadLowTimer(FREQ_770);

                    loadHighTimer(FREQ_1209);

                    myLowFrequency = FREQ_770;

                    myHighFrequency = FREQ_1209;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case '5':
                {
                    di(); 
                    loadLowTimer(FREQ_770);

                    loadHighTimer(FREQ_1336);

                    myLowFrequency = FREQ_770;

                    myHighFrequency = FREQ_1336;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case '6':
                {
                    di(); 
                    loadLowTimer(FREQ_770);

                    loadHighTimer(FREQ_1477);

                    myLowFrequency = FREQ_770;

                    myHighFrequency = FREQ_1477;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case '7':
                {
                    di(); 
                    loadLowTimer(FREQ_852);

                    loadHighTimer(FREQ_1209);

                    myLowFrequency = FREQ_852;

                    myHighFrequency = FREQ_1209;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case '8':
                {
                    di(); 
                    loadLowTimer(FREQ_852);

                    loadHighTimer(FREQ_1336);

                    myLowFrequency = FREQ_852;

                    myHighFrequency = FREQ_1336;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case '9':
                {
                    di(); 
                    loadLowTimer(FREQ_852);

                    loadHighTimer(FREQ_1477);

                    myLowFrequency = FREQ_852;

                    myHighFrequency = FREQ_1477;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case 'A':
                {
                    di(); 
                    loadLowTimer(FREQ_697);

                    loadHighTimer(FREQ_1633);

                    myLowFrequency = FREQ_697;

                    myHighFrequency = FREQ_1633;

                    mydtmfStateMachine = RUN;
                    ei();
                }break;
                
                case 'B':
                {
                    di(); 
                    loadLowTimer(FREQ_770);

                    loadHighTimer(FREQ_1633);

                    myLowFrequency = FREQ_770;

                    myHighFrequency = FREQ_1633;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case 'C':
                {
                    di(); 
                    loadLowTimer(FREQ_852);

                    loadHighTimer(FREQ_1633);

                    myLowFrequency = FREQ_852;

                    myHighFrequency = FREQ_1633;

                    mydtmfStateMachine = RUN;
                    ei();
                }break;
                
                case 'D':
                {
                    di();
                    loadLowTimer(FREQ_941);

                    loadHighTimer(FREQ_1633);

                    myLowFrequency = FREQ_941;

                    myHighFrequency = FREQ_1633;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case '*':
                {
                    di(); 
                    loadLowTimer(FREQ_941);

                    loadHighTimer(FREQ_1209);

                    myLowFrequency = FREQ_941;

                    myHighFrequency = FREQ_1209;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case '0':
                {
                    di();
                    loadLowTimer(FREQ_941);

                    loadHighTimer(FREQ_1336);

                    myLowFrequency = FREQ_941;

                    myHighFrequency = FREQ_1336;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                case '#':
                {
                    di(); 
                    loadLowTimer(FREQ_941);

                    loadHighTimer(FREQ_1477);

                    myLowFrequency = FREQ_941;

                    myHighFrequency = FREQ_1477;

                    mydtmfStateMachine = RUN;
                    ei(); 
                }break;
                
                default:
                {
                    
                }break; 
                
            }
        }
    }

}

static void gpioInitialize(void) {
    ADCON1 |= 0x0F;
    TRISAbits.RA1 = 0;
    LATAbits.LA1 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.RA4 = 1;
    TRISEbits.TRISE2 = 0; // 
    TRISEbits.TRISE0 = 0; //

    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA5 = 1;
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
    TMR0H = GET_HIGH_BYTE(TIMER0_VALUE);
    TMR0L = GET_LOW_BYTE(TIMER0_VALUE);
    T0CON = 0b10000111;
    INTCON2bits.TMR0IP = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
}

static void timer1_Init(void) {
    TMR1H = GET_HIGH_BYTE(FREQ_697_VALUE);
    TMR1L = GET_LOW_BYTE(FREQ_697_VALUE);
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

static void timer3Init(void) {
    TMR3H = GET_HIGH_BYTE(FREQ_1209_VALUE);
    TMR3L = GET_LOW_BYTE(FREQ_1209_VALUE);
    IPR2bits.TMR3IP = 0; //low priority... 
    T3CON = 0b10110001;
    PIE2bits.TMR3IE = 1; //enable timer 3
}

void loadLowTimer(lowFrequency value) {

    switch (value) {
        case FREQ_697:
        {

            TMR1H = GET_HIGH_BYTE(FREQ_697_VALUE);
            TMR1L = GET_LOW_BYTE(FREQ_697_VALUE);
        }
            break;
        case FREQ_770:
        {

            TMR1H = GET_HIGH_BYTE(FREQ_770_VALUE);
            TMR1L = GET_LOW_BYTE(FREQ_770_VALUE);

        }
            break;

        case FREQ_852:
        {

            TMR1H = GET_HIGH_BYTE(FREQ_852_VALUE);
            TMR1L = GET_LOW_BYTE(FREQ_852_VALUE);
        }
            break;

        case FREQ_941:
        {

            TMR1H = GET_HIGH_BYTE(FREQ_941_VALUE);
            TMR1L = GET_LOW_BYTE(FREQ_941_VALUE);
        }
            break;
        case FREQ_LOW_NONE:
        {
            TMR1H = GET_HIGH_BYTE(FREQ_697_VALUE);
            TMR1L = GET_LOW_BYTE(FREQ_697_VALUE);
        }
        default:
        {

        }
            break;
    }
}

void loadHighTimer(highFrequency value) {
    switch (value) {
        case FREQ_1209:
        {
            TMR3H = GET_HIGH_BYTE(FREQ_1209_VALUE);
            TMR3L = GET_LOW_BYTE(FREQ_1209_VALUE);
        }
            break;

        case FREQ_1336:
        {

            TMR3H = GET_HIGH_BYTE(FREQ_1336_VALUE);
            TMR3L = GET_LOW_BYTE(FREQ_1336_VALUE);
        }
            break;

        case FREQ_1477:
        {

            TMR3H = GET_HIGH_BYTE(FREQ_1477_VALUE);
            TMR3L = GET_LOW_BYTE(FREQ_1477_VALUE);
        }
            break;

        case FREQ_1633:
        {

            TMR3H = GET_HIGH_BYTE(FREQ_1633_VALUE);
            TMR3L = GET_LOW_BYTE(FREQ_1633_VALUE);
        }
            break;

        case FREQ_HIGH_NONE:
        {

            TMR3H = GET_HIGH_BYTE(FREQ_1209_VALUE);
            TMR3L = GET_LOW_BYTE(FREQ_1209_VALUE);
        }
            break;

        default:
        {

        }
            break;
    }
}

/*
 *         if (!PORTAbits.RA4) 
        {
            __delay_ms(20);
            if (!PORTAbits.RA4) {
                while (!PORTAbits.RA4);
                di();

                //Load timer
                loadLowTimer(FREQ_941);

                loadHighTimer(FREQ_1633);

                myLowFrequency = FREQ_941;

                myHighFrequency = FREQ_1633;

                mydtmfStateMachine = RUN;
                //load timer high

                //make it go from IDLE to running...
#if 0 
                myLowFrequency++;
                if (myLowFrequency > FREQ_LOW_NONE) {
                    myLowFrequency = FREQ_697;
                }

#endif
                ei();
            }
        }

        if (!PORTAbits.RA3) 
        {
            __delay_ms(20);
            if (!PORTAbits.RA3) {
                while (!PORTAbits.RA3);
                di();

                //Load timer
                loadLowTimer(FREQ_697);

                loadHighTimer(FREQ_1209);

                myLowFrequency = FREQ_697;

                myHighFrequency = FREQ_1209;

                mydtmfStateMachine = RUN;
                //load timer high

                //make it go from IDLE to running...
#if 0 
                myLowFrequency++;
                if (myLowFrequency > FREQ_LOW_NONE) {
                    myLowFrequency = FREQ_697;
                }

#endif
                ei();
            }
        }

        if (!PORTAbits.RA5) 
        {
            __delay_ms(20);
            if (!PORTAbits.RA5) {
                while (!PORTAbits.RA5);
                di();

                //Load timer
                loadLowTimer(FREQ_852);

                loadHighTimer(FREQ_1477);

                myLowFrequency = FREQ_852;

                myHighFrequency = FREQ_1477;

                mydtmfStateMachine = RUN;
                //load timer high

                //make it go from IDLE to running...
#if 0 
                myLowFrequency++;
                if (myLowFrequency > FREQ_LOW_NONE) {
                    myLowFrequency = FREQ_697;
                }

#endif
                ei();
            }


        }
 */