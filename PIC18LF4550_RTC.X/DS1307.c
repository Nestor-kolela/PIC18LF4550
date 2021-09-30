/*
 * File:   DS1307.c
 * Author: Nestor
 *
 * Created on January 19, 2021, 1:10 PM
 */
#include "DS1307.h"
#include "LCD.h"
#include <stdint.h>
#include "I2C.h"
#include "uart.h"

const char *eish[7] = {",Sunday", ",Monday", ",Tuesday",
    ",Wednesday", ",Thursday", ",Friday",
    ",Saturday"};

void DS1307_write(time myTime) {
    i2c_start();

    i2c_write(0xD0);

    i2c_write(0x00);

    i2c_write(myTime.seconds);

    i2c_write(myTime.minutes);

    i2c_write(myTime.hours);

    i2c_write(myTime.day);

    i2c_write(myTime.date);

    i2c_write(myTime.month);

    i2c_write(myTime.year);

    i2c_stop();
}

void DS1307_read(time * myTime) {
    i2c_start();

    i2c_write(0xD0);

    i2c_write(0x00);

    i2c_RS();

    i2c_write(0xD1);

    myTime->seconds = i2c_read(0);

    myTime->minutes = i2c_read(0);

    myTime->hours = i2c_read(0);

    myTime->day = i2c_read(0);

    myTime->date = i2c_read(0);

    myTime->month = i2c_read(0);

    myTime->year = i2c_read(1);

    i2c_stop();
}

void DS1307_Display_UART(time myTime) {
    uint8_t timeStr[11] = "00:00:00";
    uint8_t dateStr[13] = "00/00/2000";

    BCD_to_ASCII((uint8_t) (myTime.hours), timeStr);
    *(timeStr + 2) = ':';

    BCD_to_ASCII((uint8_t) (myTime.minutes), &timeStr[3]);

    *(timeStr + 5) = ':';

    BCD_to_ASCII((uint8_t) (myTime.seconds), &timeStr[6]);
    
    *(timeStr + 10) = '\0';

    //for date

    BCD_to_ASCII((uint8_t) (myTime.date), dateStr);
    *(dateStr + 2) = '/';

    BCD_to_ASCII((uint8_t) (myTime.month), &dateStr[3]);

    *(dateStr + 5) = '/';

    BCD_to_ASCII((uint8_t) (myTime.year), &dateStr[8]);
    
    *(dateStr + 12) = '\0';

    UART_puts((char *) timeStr);
    UART_puts((char *) dateStr);
    
    LCD_goto(1,1);
    LCD_puts((char *)timeStr);
    LCD_goto(2,1);
    LCD_puts((char *) dateStr);
    LCD_goto(2,11); 
    LCD_putrs(eish[myTime.day - 1]);
}

static void BCD_to_ASCII(uint8_t valueInBCD, uint8_t * ptr) {
    *ptr++ = ((valueInBCD >> 4) | 0x30);
    *ptr = ((valueInBCD & 0x0F) | 0x30);
}