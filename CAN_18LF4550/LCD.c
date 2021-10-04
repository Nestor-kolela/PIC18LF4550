
/*##############################################################################
 # Filename: Lcd.c
 #     Date: 2018/03/02
 #  Version: 1.45
 #   Device: PIC16F877A
 # Synopsis: Functions to control the Hitachi (HD44780U) dot matrix liquid
 #           crystal display (LCD) driver.
 #
 #   Author: KALAMBAY NK
 #############################################################################*/

/*--- Header for special function register and peripheral definitions --------*/
#include    <xc.h>

/*--- Header for Library function definitions --------------------------------*/
//#include    <stdlib.h>

/*--- Header for global user function, variable and constant definitions -----*/
#include    "LCD.h"

/*--- Local function declarations --------------------------------------------*/
//void XXX (void);

/*--- Local variable declarations --------------------------------------------*/
//unsigned char DR1;

/*--- Local Constant declarations --------------------------------------------*/

#define _XTAL_FREQ 16000000      //Required for "__delay_ms()"

//#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/16000000.0)))
//#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/16000.0)))

/*------- Start of relocatable function routines -----------------------------*/

/*==============================================================================
 = Function: LCD_send
 = Synopsis: Write instruction (RS = 0) or data (RS = 1) to LCD in 4-bit mode
 =============================================================================*/
void LCD_send(char RS, unsigned char data)
{
    LCD_RS = RS,0;    
    LCD_DATA &= 0xF0;               //Clear low nibble for OR operation
    LCD_DATA |= ((data>>4) & 0x0F); //Load high nibble data
    STROBE();                       //Clock in high data nibble
    LCD_DATA &= 0xF0;               //Clear low nibble for OR operation
    LCD_DATA |= (data & 0x0F);      //Load low data nibble
    STROBE();                       //Clock in low data nibble
    __delay_ms(5);
}

/*==============================================================================
 = Function: LCD_init
 = Synopsis: Initialize the LCD - before anything else
 =============================================================================*/
void LCD_init(void)
{
    LCD_RS = INSTR;                 //Ensure instruction mode selected
    __delay_ms(15);                 //Wait 15mSec after power is applied
    LCD_DATA = 0x03;                //Manufacturer Init command enable 8bit mode
    STROBE();                       //High byte of Function set
    __delay_ms(5);

    LCD_DATA = 0x03;                //Manufacturer Init command enable 8bit mode
    STROBE();                       //High byte of Function set
    __delay_ms(5);

    LCD_DATA = 0x02;                //Enable 4bit mode
    STROBE();                       //High byte of Function set
    __delay_ms(5);
    
    LCD_send(INSTR,0b00101100);     //Select 4bit, 2 line & 5x10 font
    __delay_ms(5);
    LCD_send(INSTR,0b00000001);     //Clear screen command
    __delay_ms(5);
    LCD_send(INSTR,0b00001100);     //Display on, cursor off, blink off
}

/*==============================================================================
 = Function: LCD_clear
 = Synopsis: Clear and home cursor on LCD
 =============================================================================*/
void LCD_clear(void)
{
    LCD_send(INSTR,0b00000001);
    __delay_ms(2);
}

/*==============================================================================
 = Function: LCD_goto
 = Synopsis: Move cursor to specified postion on LCD
 =============================================================================*/
void LCD_goto(unsigned char x, unsigned char y)
{
    if(x == 1)
        LCD_send(INSTR,(0x80 + y-1));
    else if(x == 2)
        LCD_send(INSTR,(0xC0 + y-1));
    else if(x == 3)
        LCD_send(INSTR,(0x94 + y-1));
    else if(x == 4)
        LCD_send(INSTR,(0xD4 + y-1));
    __delay_ms(2);
}

/*==============================================================================
 = Function: LCD_putrs
 = Synopsis: Write a string of characters from ROM to LCD
 =============================================================================*/
void LCD_putrs(const char *s)
{
    while(*s)
        LCD_send(DATA,*(s++));
}

/*==============================================================================
 = Function: LCD_puts
 = Synopsis: Write a string of characters from RAM to LCD
 =============================================================================*/
void LCD_puts(char *s)
{
    while(*s)
        LCD_send(DATA,*(s++));
}

/*==============================================================================
=   Function: AddSpaces
= Parameters: Maximum required string size and actual string size
=   Synopsis: Adds spaces infront for number string display.
==============================================================================*/
void AddSpaces(unsigned char MaxLen, char StrLen)
{
    /* Local defined variables */
    unsigned char Spaces;
    unsigned char Cnt;

    Spaces = (MaxLen - StrLen);

    for(Cnt = 1; Cnt <= Spaces; Cnt++)
    {
        LCD_send(DATA,' ');
    } /* For loop end */
}

/*==============================================================================
 = Function: LCD_putsLen
 = Synopsis: Write required lenght of string characters from RAM to LCD
 =============================================================================*/
void LCD_putsLen(char *s, char clen)
{
    char cCnt;
    for(cCnt = 0; cCnt < clen; cCnt++)
        LCD_send(DATA,*(s++));
}