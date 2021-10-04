/*
 * File:   DS18B20.c
 * Author: Nestor
 *
 * Created on February 4, 2021, 3:17 PM
 */


#include <xc.h>
#include "DS18B20.h"

void DS13B20_Init(void)
{
    SetAsInput(); //set as input first
    Setasoutput(); //set as output
    __delay_us(500);
    SetAsInput();
    __delay_us(70);
    
}
uint8_t DS18B20_read(void)
{
    
}

static void BitBangWrite(uint8_t byte)
{
    Setasoutput();
    for(uint8_t count = 0; count < 8; count++)
    {
        PIN = (byte >> count) & (0b00000001);
        WAIT();
    }
}
static uint8_t BitbangRead(void)
{
    uint8_t tempVar = 0;
    SetAsInput();
    for(uint8_t count = 0; count < 8; count++)
    {
        tempVar |= PIN;
        tempVar <<= count;
    }
    return tempVar;
}

static void SetAsInput(void)
{
    PIN_IN_OR_OUT = 1;
}
static void Setasoutput(void)
{
    PIN_IN_OR_OUT = 0;
}

