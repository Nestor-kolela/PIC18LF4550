/*
 * File:   main.c
 * Author: nestor
 *
 * Created on September 30, 2021, 8:07 PM
 */

#include <xc.h>
#include "config.h"
#include "uart.h"
#include "I2C.h"
#include "LCD.h"
#include <stdio.h>
#include <stdlib.h>
#include "DS1307.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/*
 * interrupt service routine
 */
#define _XTAL_FREQ  16000000

#define LED2        LATCbits.LATC0  //LED on 
#define PB_RC2      PORTCbits.RC2 //push button on RC2
#define PB_RA3      PORTAbits.RA3 //push button on RA3
#define PB_RB2      PORTBbits.RB2 //push button on INT2
#define Delay20Ms()   __delay_ms(20);

void Interrupt_Init(void);
void ISR(void);
void timerZero_Init(void);
static void Ports_Init(void); //init ports

/*
 * Global varibales
 */

unsigned char myIP[16] = {0};
volatile uint8_t seconds = 0; // seconds variables
volatile uint8_t state_machine = 0;
volatile uint8_t dummy = 0;

//extern char * htmlPtr; 

extern const char * EISH;

volatile uint8_t flag = 0; 

void __interrupt(high_priority) myISR_high(void) {
    if (PIE1bits.RC1IE && PIR1bits.RC1IF) {
        UART_rx_complete_irq();
    }//end if for UART receive reception
    if (PIE1bits.TX1IE && PIR1bits.TX1IF)
    {
        UART_tx_udr_empty_irq();
    }
}//end of interrupt

void __interrupt(low_priority) myISR_low(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        flag = 1; 
        TMR0H = 0xC2;
        TMR0L = 0xF7;
        INTCONbits.TMR0IF = 0;
    }//end of interrupt routine for timer
}
/*******************************************************************************
 * Function Prototype
 ******************************************************************************/

void Enable_Interrupt(void);
void Disable_Interrupt(void);
void Disable_WatchDog(void); //disable watch dog timer
void Enable_WatchDog(void); //enable watch dog timer


static void timerStart(void); //start the timer
static void timerStop(void); //stop the timer

void main(void) {
    
    time now;

    Ports_Init();
    
    LCD_init();

    UART_Init(115200);

    I2C_INTIALIZE(100000);
    
    timerZero_Init();

    Interrupt_Init();
    
    LCD_clear(); //clear

    timerStart();
    
    Enable_Interrupt(); 
    
    while (1) 
    {
        if(flag)
        {
            flag = 0;
            DS1307_read(&now);
            DS1307_Display_UART(now);
        }
    }//end of while loop
    return;
}

void timerZero_Init(void) {
    TMR0H = 0xC2;
    TMR0L = 0xF7;
    T0CON = 0b10000111;
    INTCON2bits.TMR0IP = 0;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
}

static void timerStart(void)
{
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON = 1;
    INTCONbits.TMR0IE = 1;
}

static void timerStop(void)
{
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 0;
}

void Interrupt_Init(void) {
    INTCONbits.GIE = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    INTCONbits.PEIE = 1; //enable peripheral interrupt
    INTCONbits.PEIE_GIEL = 1;
    RCONbits.IPEN = 1;
}

static void Ports_Init(void)
{
    ADCON1 = 0b00001111; //VSS, VDD, then DIGITAL FOR all inputs
    TRISAbits.TRISA1 = 0; //output
    
    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA3 = 0;
    
    TRISD = 0x00;
    LATD = 0x00; 
    
    TRISCbits.RC0 = 0; //for LED2
    LED2 = 0;
    
    

    TRISCbits.TRISC2 = 1; //input connected on RC2
    
    TRISAbits.TRISA3 = 1; //input connected on RC3
    

    INTCON2bits.INTEDG2 = 0; //interrupt on falling edge
    
    INTCON3bits.INT2IE = 1; //enable the INT2 EXTERNAL INTERRUPT
    
    INTCON3bits.INT2IP = 0; //low priority
    TRISBbits.TRISB2 = 1; //input connected on RB2
}

void Enable_Interrupt(void)
{
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}//end enable interrupt

void Disable_Interrupt(void)
{
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
}//end disable interrupt

void Enable_WatchDog(void)
{
    WDTCONbits.SWDTEN = 1;
}

void Disable_WatchDog(void)
{
    WDTCONbits.SWDTEN = 0;
}
