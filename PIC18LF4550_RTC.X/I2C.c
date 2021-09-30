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
#include "uart.h"
#include "LCD.h"
#define _XTAL_FREQ  16000000
void I2C_INTIALIZE(uint24_t clock) {    
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    SSPSTATbits.SMP = 1;
    SSPSTATbits.CKE = 0;
    
    SSPCON1 |= 0x28; //no collision, no overflow, enable I2C, Master mode
    SSPCON2 |= 0x00;
    SSPADD = (uint8_t)(_XTAL_FREQ / (clock * 4)) - 1; //we multiply by 1000 to define frequency kilo Hertz
}

void i2c_start(void) {
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN); //wait for start to complete
    PIR1bits.SSPIF = 0; //clear Interrupt flag
}

void i2c_stop(void) {
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN);
    PIR1bits.SSPIF = 0; //clear Interrupt flag
}

void i2c_RS(void) {
    SSPCON2bits.RSEN = 1;
    while (SSPCON2bits.RSEN);
    PIR1bits.SSPIF = 0;
}

char i2c_read(uint8_t ACK_NACK) 
{
    SSPSTATbits.BF = 0;
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF); //wait for buffer to be full 
    SSPCON2bits.ACKDT = ACK_NACK;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    return SSPBUF;
}

void i2c_write(uint8_t data) 
{
    SSPBUF = data;
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    //if (SSPCON2bits.ACKSTAT) { //if slave has not responded after the ninth bit stop transmission
    //    i2c_stop();
    //}
}

void i2c_scanBus(void) 
{
    char eish[15];
    uint8_t row = 1;
    uint8_t column = 1;

    for (uint8_t address = 1; address <= 128; address++) {
        i2c_start();
        i2c_write(address);
        if (!SSPCON2bits.ACKSTAT) {
            sprintf((char *) eish, "%u", address);
            LCD_goto(row, column);
            column += 4;
            if (column >= 16) {
                column = 1;
                row++;
            }
            if (row >= 4) {
                row = 1;
            }
            LCD_puts((char *) eish); //print out slave address found on the bus
            SSPCON2bits.ACKSTAT = 1;
        }
        i2c_stop();
    }
    
    
}

void i2c_clrBuf(void) 
{
    i2c_start();
    i2c_write(0x00);
    i2c_stop();
}