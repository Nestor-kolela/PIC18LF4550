#ifndef _KEYPAD_H
#define _KEYPAD_H

#include <xc.h>


#define KEYPAD_PORT             PORTD
#define KEYPAD_DIRECTION_REG    TRISD

/*
 *  Keypad Layout below
 *      Column 1    Column 2    Column 3    Column 4
 * Row 1    1           2           3           A 
 * Row 2    4           5           6           B
 * Row 3    7           8           9           C
 * Row 4    *           0           #           D
 */

#define COLUMN1         PORTDbits.RD0
#define COLUMN2         PORTDbits.RD1   
#define COLUMN3         PORTDbits.RD2
#define COLUMN4         PORTDbits.RD3

#define ROW1            PORTDbits.RD4
#define ROW2            PORTDbits.RD5   
#define ROW3            PORTDbits.RD6   
#define ROW4            PORTDbits.RD7

#define COLUMN1_DIR     TRISDbits.RD0
#define COLUMN2_DIR     TRISDbits.RD1
#define COLUMN3_DIR     TRISDbits.RD2
#define COLUMN4_DIR     TRISDbits.RD3

#define ROW1_DIR        TRISDbits.TRISD4
#define ROW2_DIR        TRISDbits.TRISD5
#define ROW3_DIR        TRISDbits.TRISD6
#define ROW4_DIR        TRISDbits.TRISD7

#define _XTAL_FREQ  48000000UL

void Keypad_Init(void); 
int8_t Keypad_Sample(void); 

#endif