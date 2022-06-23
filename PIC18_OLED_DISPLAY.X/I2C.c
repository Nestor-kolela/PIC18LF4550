/*
 * File:   i2c.c
 * Author: Nestor
 *
 * Created on 25 April 2020, 6:57 PM
 */

#include <pic18lf4550.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2C.h"
//#include "uart.h"
//#include "LCD.h"
#include <string.h>
#define _XTAL_FREQ  48000000

extern void putUSBUSART(uint8_t *data, uint8_t  length); 
void I2C_INTIALIZE(uint24_t clock) {    
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    SSPSTATbits.SMP = 1;
    SSPSTATbits.CKE = 0;
    
    SSPCON1 |= 0x28; //no collision, no overflow, enable I2C, Master mode
    SSPCON2 |= 0x00;
    SSPADD = (uint8_t)(_XTAL_FREQ / (clock * 4)) - 1; //we multiply by 1000 to define frequency kilo Hertz
}

void I2C_start(void) {
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN); //wait for start to complete
    PIR1bits.SSPIF = 0; //clear Interrupt flag
}

void I2C_stop(void) {
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN);
    PIR1bits.SSPIF = 0; //clear Interrupt flag
}

void I2C_RS(void) {
    SSPCON2bits.RSEN = 1;
    while (SSPCON2bits.RSEN);
    PIR1bits.SSPIF = 0;
}

char I2C_read(uint8_t ACK_NACK) 
{
    SSPSTATbits.BF = 0;
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF); //wait for buffer to be full 
    SSPCON2bits.ACKDT = ACK_NACK;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    return SSPBUF;
}

void I2C_Write(uint8_t data) 
{
    SSPBUF = data;
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    //if (SSPCON2bits.ACKSTAT) { //if slave has not responded after the ninth bit stop transmission
    //    i2c_stop();
    //}
}

void I2C_scanBus(void) 
{
    char eish[15];

    for (uint8_t address = 1; address <= 128; address++) {
        I2C_start();
        I2C_Write(address);
        if (!SSPCON2bits.ACKSTAT) {
            //sprintf((char *) eish, "%u", address);
            //putUSBUSART((uint8_t *) eish, (uint8_t) strlen((const char *) eish));
            //SSPCON2bits.ACKSTAT = 1;
        }
        I2C_stop();
    }
    
}

void I2C_clrBuf(void) 
{
    I2C_start();
    I2C_Write(0x00);
    I2C_stop();
}