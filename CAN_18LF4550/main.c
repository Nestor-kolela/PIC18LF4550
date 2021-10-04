/*
 * File:   main.c
 * Author: Nestor
 *
 * Created on November 21, 2020, 8:52 PM
 */


#include <xc.h>
#include "config.h"
#include <stdio.h>
#include <stdlib.h> //include library
#include <stdint.h>
#include "SPI.h"
#include <stdbool.h> 
#include "LCD.h" //init LCD
#include "MCP2515.h"
#include <string.h>
typedef enum{OFF = (uint8_t) 0, ON = (uint8_t) 1 } status;
volatile status myStatus = OFF;

typedef enum
{
    FIRST = (uint8_t) 0, SECOND = (uint8_t) 1
}StateForPB;

volatile StateForPB myStateForPB = FIRST;
/*******************************************************************************
 * Define MACROS
 ******************************************************************************/
#define LED         LATAbits.LATA1
#define PB_RA4      PORTAbits.RA4
#define _XTAL_FREQ  16000000
#define LED2        LATCbits.LATC0  //LED on
#define Delay20Ms()   __delay_ms(20);
#define PB_RB2      PORTBbits.RB2
#define dSTANDARD_CAN_MSG_ID_2_0B 1
#define dEXTENDED_CAN_MSG_ID_2_0B 2
/*******************************************************************************
 * Interrupt service routine
 ******************************************************************************/
void __interrupt(high_priority) myISR_high(void) {
    if (INTCON3bits.INT2IE && INTCON3bits.INT2IF)
    {
        myStateForPB = SECOND;
        INTCON3bits.INT2IF = 0;
    }//interrupt on change
}//end of interrupt

void __interrupt(low_priority) myISR_low(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        TMR0H = 0xC2;
        TMR0L = 0xF7;
        myStatus = ON;
        INTCONbits.TMR0IF = 0;
    }//end of interrupt routine for timer
}//end low priority

/*
 * Function prototype
 */
static void Interrupt_Init(void);
static void timerZero_Init(void);
static void Ports_Init(void);

void main(void) {
   
    char eish[20] = {0};
    
    char buffer[9] = {0};
     
    char bufferForTemp[9] = {0}; //buffer to store the values from temperature sensor
    
    char bufferForPot[9] = {0}; //buffer for store the values read from pot

    typedef union {
        uint8_t value;

        struct {
            unsigned ZERO : 1;
            unsigned ONE : 1;
            unsigned TWO : 1;
            unsigned THREE : 1;
            unsigned FOUR : 1;
            unsigned FIVE : 1;
            unsigned SIX : 1;
            unsigned SEVEN : 1;
        };
    } VAR;
    
    
    
    typedef union
    {
        uint8_t value;
        struct
        {
            unsigned flagZero: 1;
            unsigned flatOne: 1;
            unsigned flagTwo: 1;
            unsigned flagThree: 1;
            unsigned flagFour: 1;
            unsigned flagFive: 1;
            unsigned flagSix: 1;
            unsigned flagSeven: 1;
        };
    }Flag;
    
    
    VAR myVAR;
    Flag myFlagOne, myFlagTwo;

    myFlagOne.value = 0;
    
    myVAR.value = 0;
    
    myFlagTwo.value = 0;
    
    Ports_Init(); //init all the ports
    
    Interrupt_Init();
    
    timerZero_Init(); //

    LCD_init();
    
    LCD_clear(); //clear
    
    LCD_puts("Nestor Kolela");
    
    LCD_goto(3,1);
    
    LCD_putrs("Helene Ngalula");
    
    LCD_goto(4,1);
    
    LCD_putrs("And Kalambay");
    
    SPI_Init();
    
    MCP2515_Init(); //init the MCP2515

    myVAR.value = MCP2515_read(CANSTAT0);
    
    sprintf(eish, "0x%X", myVAR.value);
    
    LCD_goto(2, 1);
    
    LCD_puts(eish);

    LED = 1;

    typedef union {

        struct {
            uint8_t data0;
            uint8_t data1;
            uint8_t data2;
            uint8_t data3;
            uint8_t data4;
            uint8_t data5;
            uint8_t data6;
            uint8_t data7;
            uint8_t dlc;
            uint8_t idType;
            uint32_t id;          
        } frame;
        uint8_t array[14];
    } uCAN_MSG;
    
    uCAN_MSG bufferOne;
    
    for(uint8_t cnt = 0; cnt < 14; cnt++)
    {
        bufferOne.array[cnt] = cnt;
    }
    
    while(1) 
    {
        if (myStateForPB == SECOND) 
        {
            myStateForPB = FIRST;
            //handle the interrupt on change
            myVAR.value = MCP2515_read(CANINTF);
            //interrupt from RX0IE
            LED ^= 1;
            
            if(myVAR.ZERO == true) //if interrupt is set RX0IF
            {
                //read the registers
                CONFIG_REGISTER(CANINTF, BIT0, 0x00); // clear the interrupt for this
                myFlagOne.value = MCP2515_read(RXB0SIDL);
                
                if(myFlagOne.flagThree == 0)
                {
                    //This was a standard frame
                    //1) data frame
                    
                    if(myFlagOne.flagFour == 0)
                    {
                        //read the value to determine the length of the data                       
                        //here we must first read the identifier
                        //to know what type of data it is
                        //Yes
                        uint16_t msgIdentifier = myFlagOne.value >> 5; //only read bit 7-6-5
                        msgIdentifier |= (uint16_t)(MCP2515_read(RXB0SIDH) << 3) ; //read the remaining data

                        
                        if (msgIdentifier == ID_FOR_TEMP) 
                        {
                            // if this is for temperature 
                            //then read it into the temperature buffer
                            myFlagTwo.value = MCP2515_read(RXB0DLC);

                            if ((myFlagTwo.value & 0x0F) == 0) //AND it with 0x0F
                            {
                                //if it is zero then do nothing
                            } else 
                            {
                                uint8_t tempVar = 0;
                                //tempVar = myFlagTwo.value & 0x07;
                                while (tempVar < (myFlagTwo.value & 0x0F)) 
                                {
                                    *(bufferForTemp + tempVar) = MCP2515_read(RXB0D0 + tempVar);
                                    tempVar++; //read the data
                                }
                            }
                            
                        } else if (msgIdentifier == ID_FOR_POT) 
                        {
                            // if this is for temperature 
                            //then read it into the temperature buffer
                            myFlagTwo.value = MCP2515_read(RXB0DLC);

                            if ((myFlagTwo.value & 0x0F) == 0) //AND it with 0x0F
                            {
                                //if it is zero then do nothing
                            } else 
                            {
                                uint8_t tempVar = 0;
                                //tempVar = myFlagTwo.value & 0x07;
                                while (tempVar < (myFlagTwo.value & 0x0F)) 
                                {
                                    *(bufferForPot + tempVar) = MCP2515_read(RXB0D0 + tempVar);
                                    tempVar++; //read the data
                                }
                            }
                        }
                    }else //handle remote frame
                    {
                        //make sure you send the data requested
                        //here you are handling the remote frame
                        //you must send the requested data                       
                        //Call a certain function
                        uint16_t receivedIdentifier = 0;
                        receivedIdentifier = MCP2515_read(RXF0SIDL);
                        receivedIdentifier >>= 5; //get the SID2, SID1, SID0
                        receivedIdentifier |= (uint16_t)(MCP2515_read(RXF0SIDH) << 3);
                        
                        if(receivedIdentifier == ID_FOR_TEMP)
                        {
                            //if the receivedIdentifier is for TEMP
                            const char * constTemp = "12345678";
                            //load TXBnSIDH
                            //Load TXBnnSIDL
                            //TXBnDLC also
                            //if data bytes are present in the message
                            //then load TXBnDm registers as well
                            //if the message is to use extemded idenfitiers 
                            //then load EXIDE as well found in TXBnEIDm registers
                            //Remember to either enable or disable the generation of interrupts
                            
                            //use SPI write command
                            //or use RTS command
                            
                            //if transmission is initiated via the SPI interface
                            //the TXREQ can be set at the same time as the TXPx priorities bits
                            
                            //once TXREQ is set, the ABTF, MLOA and TXERR bits 
                            //will be automatically cleared.
                            
                            //select the identifier
                            //then the length of the data to be sent
                            MCP2515_transmitStand((uint8_t) strlen(constTemp), ID_FOR_TEMP, (uint8_t *) constTemp, 0, 0); 
                            
                        }else if(receivedIdentifier == ID_FOR_POT)
                        {
                            //if the receivedIdentifier is for POT
                            //then call function for POTENTIOMETER
                            const char * constPort = "98765432";
                                                        //load TXBnSIDH
                            //Load TXBnnSIDL
                            //TXBnDLC also
                            //if data bytes are present in the message
                            //then load TXBnDm registers as well
                            //if the message is to use extemded idenfitiers 
                            //then load EXIDE as well found in TXBnEIDm registers
                            //Remember to either enable or disable the generation of interrupts
                            
                            //use SPI write command
                            //or use RTS command
                            
                            //if transmission is initiated via the SPI interface
                            //the TXREQ can be set at the same time as the TXPx priorities bits
                            
                            //once TXREQ is set, the ABTF, MLOA and TXERR bits 
                            //will be automatically cleared. 
                            
                            MCP2515_transmitStand((uint8_t) strlen(constPort), ID_FOR_TEMP, (uint8_t *) constPort, TRANSMIT_BUFFER_0, DATA_FRAME); 
                        }
                    }//end if it is data frame
                    
                }//end else if myFlagThree == 1
                else 
                {
                    //This was an Extended Frame   
                    //if it is extended frame
                    //then check if it is remote frame or data frame
                    if(myFlagOne.flagFour == 0) 
                    {
                        myFlagTwo.value = MCP2515_read(RXB0DLC); //read the data length for this
                        if ((myFlagTwo.value & 0x0F) == 0) 
                        {
                            //if by anding this, we get ZERO THEN IT MEANS
                            ///the data length is zero
                        } else 
                        {
                            uint8_t tempValue = 0;
                            while (tempValue < (myFlagTwo.value & 0x0F)) 
                            {
                                //keep reading until all the bytes are received
                                *(buffer + tempValue) = MCP2515_read(RXB0D0 + tempValue);
                                tempValue++;
                            }
                        } // if the data length is greater than zero
                    }else //if(myFlagOne.flagFour == 0) 
                    {
                        uint32_t receivedIdentifier = 0;
                        //receivedIdentifier = (uint32_t) (MCP2515_read(RXB0SIDL));
                        //receivedIdentifier <<= 27u;
                        receivedIdentifier = (uint32_t)(MCP2515_read(RXB0EID0));
                        receivedIdentifier |= (uint32_t)(MCP2515_read(RXB0EID8) << 8u);
                        receivedIdentifier |= (uint32_t)((MCP2515_read(RXB0SIDL) & 0b00000111)) << 16u;
                        receivedIdentifier |= (uint32_t)((MCP2515_read(RXB0SIDL) & 0b11100000)) << 19u;
                        receivedIdentifier |= (uint32_t)(MCP2515_read(RXB0SIDH)) << 22u;
                        
                        if(receivedIdentifier == ID_EX_FOR_POT)
                        {
                            //then send the data for
                            //potentiometer
                            
                            
                            //void MCP2515_transmitStand(U8 dtLen, uint16_t msgID, const U8 * ptr, U8 buf, U8 RTR)
                            //MCP2515_transmitStand(strlen())
                        }else if(receivedIdentifier == ID_EX_FOR_TEMP)
                        {
                            //then send the data for temperature
                            //MCP2515_transmitStand
                        }
                    }//end function for flagOne is an extended remote frame

                }//end else
                //clear the flags
                CONFIG_REGISTER(CANINTF, BIT0, 0x00); //the flag that caused the interrupt
                
            }
            //interrupt from RX1IF
            if(myVAR.ONE == true)
            {
                CONFIG_REGISTER(CANINTF, BIT1, 0x00); //clear the flag
                myFlagOne.value = MCP2515_read(RXB1SIDL);
                //check if the message is an extended identifer or a standard frame
                
                if(myFlagOne.flagThree == 0) //meaning it is standard identifier
                {
                    //handle the standard message
                    //bufferOne.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
                    //bufferOne.frame.id = (myFlagOne.value >> 3); // read ///////////////////the 3 highest bits
                    //////////bufferOne.frame.id |= (myFlagOne.value //////////////// );
                    
                    //1) First check if it is standard identifier or extended 
                    
                    //2) then Check if it a data frame or a remote frame
                    if(myFlagOne.flagFour == 0) //this is for data frame
                    {
                        //read the data
                        bufferOne.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
                        bufferOne.frame.id = (myFlagOne.value >> 5); //get the 8 MSB
                        bufferOne.frame.id |= (uint32_t) MCP2515_read(RXB1SIDH) << 3;
                        
                        //collect the data length brother... 
                        //then display the received data
                        
                        bufferOne.frame.dlc = MCP2515_read(RXB1DLC) & 0x0F; //get only the lower nibble
                        uint8_t tempCount = 0;
                        while(tempCount < bufferOne.frame.dlc)
                        {
                            bufferOne.array[tempCount] = (uint8_t)(RXB1D0 + tempCount);
                            tempCount++;
                        }
                        if(bufferOne.frame.id == ID_FOR_POT)
                        {
                            //identifier for potentiometer
                            //then do something about it
                        }else if(bufferOne.frame.id == ID_FOR_TEMP)
                        {
                            //identifier for temperature LOL
                            
                        }
                    }else // this is for remote frame
                    {
                        //send the requested information
                        
                        //check the identifier
                        
                        bufferOne.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
                        bufferOne.frame.id = (myFlagOne.value >> 5);
                        bufferOne.frame.id |= (uint32_t) (MCP2515_read(RXB1SIDH) << 3); //get the ID
                        
                        if(bufferOne.frame.id == ID_FOR_TEMP)
                        {
                            //Send the data for temperature
                            //void MCP2515_transmitStand(U8 dtLen, uint16_t msgID, const U8 * ptr, U8 buf, U8 RTR)
                            const char tempSensor[] = "35 Deg";
                            MCP2515_transmitStand((uint8_t) strlen(tempSensor), (uint16_t) bufferOne.frame.id, (uint8_t *)tempSensor, TRANSMIT_BUFFER_1, DATA_FRAME); //
                        }else if(bufferOne.frame.id == ID_FOR_POT)
                        {
                            //send the data for the potentiometer
                            //void MCP2515_transmitStand(U8 dtLen, uint16_t msgID, const U8 * ptr, U8 buf, U8 RTR);
                            const char potSensor[] = "POT:1234";
                            MCP2515_transmitStand((uint8_t) strlen(potSensor), (uint16_t) bufferOne.frame.id, (uint8_t *) potSensor, TRANSMIT_BUFFER_1, DATA_FRAME);
                        }
                        //then send the required data
                        
                    }//this is for remote frame brother... 
                }else if(myFlagOne.flagThree == 1) //handle the extended message
                {
                    //bufferOne.frame.idType = dEXTENDED_CAN_MSG_ID_2_0B; // read the identifier
                    if(myFlagOne.flagFour == 0) //data frame
                    {
                        bufferOne.frame.idType = dEXTENDED_CAN_MSG_ID_2_0B;
                        bufferOne.frame.id = MCP2515_read(RXB1EID0); //get this bit
                        bufferOne.frame.id |= (uint32_t) MCP2515_read(RXB1EID8) << 8u;
                        bufferOne.frame.id |= (uint32_t) (MCP2515_read(RXB1SIDL) & 0b00000111) << 16u;
                        bufferOne.frame.id |= (uint32_t) (MCP2515_read(RXB1SIDL) & 0b11100000) << 19u;
                        bufferOne.frame.id |= (uint32_t) MCP2515_read(RXB1SIDH) << 22u;
                        
                        
                    }else
                    {
                        //this is to handle remote frame
                        
                    }//end myFlagOne.flagFour
                }
                
            }
            
            if(myVAR.TWO == true) //interruuupt from TX0IF
            {
                CONFIG_REGISTER(CANINTF, BIT2, 0x00); //clear the flag
            }
            
            if(myVAR.THREE == true) // interrupt from TX1IF
            {
                CONFIG_REGISTER(CANINTF, BIT3, 0x00); //clear the flag for 
            }
            
            if(myVAR.FOUR == true) // interrupt from TX2IF
            {
                CONFIG_REGISTER(CANINTF, BIT4, 0x00);
            }
            
            if(myVAR.FIVE == true) //interrupt from ERRIF
            {
                CONFIG_REGISTER(CANINTF, BIT5, 0x00);
            }
            
            if(myVAR.SIX == true) //wake-up interrupt flag-bit
            {
                CONFIG_REGISTER(CANINTF, BIT6, 0x00);
            }
            
            if(myVAR.SEVEN == true) //message error interrupt flag bit
            {
                CONFIG_REGISTER(CANINTF, BIT7, 0x00);
            }
            //Clear the interrupt RX0IF in CANINTF must be cleared
        }
        
        //asm("SLEEP");
        //asm("NOP");
    }//end while
    return; //return
}//end main

static void timerZero_Init(void) {
    TMR0H = 0xC2;
    TMR0L = 0xF7;
    T0CON = 0b10000111;
    INTCON2bits.TMR0IP = 0;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
}

static void Interrupt_Init(void) {
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    INTCONbits.PEIE = 1; //enable peripheral interrupt
    INTCONbits.PEIE_GIEL = 1;
}
static void Ports_Init(void)
{
    ADCON1 = 0b00001111; //VSS, VDD, then DIGITAL FOR all inputs
    TRISAbits.TRISA1 = 0; //output
    LATAbits.LATA1 = 0;
    TRISAbits.TRISA4 = 1;
 
    TRISD = 0x00;
    LATD = 0x00; 
    
    TRISAbits.TRISA3 = 1; //input connected on RC3
    
    TRISCbits.RC0 = 0;
    
    INTCON2bits.INTEDG2 = 0; //interrupt on falling edge
    
    INTCON3bits.INT2IE = 1; //enable the INT2 EXTERNAL INTERRUPT
    
    INTCON3bits.INT2IP = 1; //low priority
    
    TRISBbits.TRISB2 = 1; //input connected on RB2
    
    TRISBbits.TRISB3 = 0; //output for MCP2515 CS
}