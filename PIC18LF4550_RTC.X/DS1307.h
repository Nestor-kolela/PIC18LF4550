/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef DS1307_H
#define	DS1307_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} time;


void DS1307_write(time myTime);
static void BCD_to_ASCII(uint8_t valueInBCD, uint8_t * ptr);
void DS1307_Display_UART(time myTime);
void DS1307_read(time * myTime);
#endif

