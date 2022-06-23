#include "sysconfig.h"
#include <xc.h>
#include "main.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "SSD1306.h"
#include "I2C.h"

bool TimerInterrupt = false;

#define LED_PIN PORTAbits.RA1

void __interrupt(high_priority) mainISR (void)
{
    if(INTCON3bits.INT2IE && INTCON3bits.INT2IF)
    {
        
        INTCON3bits.INT2IF = 0; 
    }
}


void __interrupt(low_priority) myISR_low(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        TMR0H = 0xC2;
        TMR0L = 0xF7;
        TimerInterrupt = true; 
        
        INTCONbits.TMR0IF = 0;
    }//end of interrupt routine for timer    
}//end low priority

static void Ports_Init(void); 
static void Interrupt_Init(void); 
static void timerZero_Init(void);

void main(void) 
{

    
    Interrupt_Init(); //set all the interrupts
    
    Ports_Init(); //configure the ports
    
    
    timerZero_Init(); 
    
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
    
    uint8_t tempBuf[40]; 
    uint8_t second = 0; 
    while(1)
    {        
        if(TimerInterrupt == true)
        {
            /*
             * Do all the ADC conversion here 
             */
            //SSD1306_Clear();
            SSD1306_GotoXY(0, 0);
            SSD1306_Puts("Fey-Tech", &Font_7x10, 1);
            SSD1306_GotoXY(0, 10);
            SSD1306_Puts("Designer:", &Font_7x10, 1);
            SSD1306_GotoXY(0, 20);
            SSD1306_Puts("www.feytech.co.za", &Font_7x10, 1);
            SSD1306_GotoXY(0, 30);
            SSD1306_Puts("Nestor Kalambay", &Font_7x10, 1);
            
            sprintf(tempBuf, "Seconds: %d", second++);
            
            
            SSD1306_GotoXY(0, 40);
            SSD1306_Puts(tempBuf, &Font_7x10, 1); 
            SSD1306_UpdateScreen(); //display
            
            if(second == 255)
            {
                second = 0; 
                SSD1306_Clear();
            }
            LED_PIN ^= 1; 
            INTCONbits.GIE = 0; 
            TimerInterrupt = false; 
            INTCONbits.GIE = 1; 
        }
        
    }
    
    return;
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
    
    INTCON3bits.INT2IP = 1; //set it to 1 for high priority
    
    TRISBbits.TRISB2 = 1; //input connected on RB2
    
    TRISBbits.TRISB3 = 0; //output for MCP2515 CS

}

static void timerZero_Init(void) {
    TMR0H = 0xC2;
    TMR0L = 0xF7;
    T0CON = 0b10000111;
    INTCON2bits.TMR0IP = 0;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
}