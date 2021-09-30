/*##############################################################################
 # Filename: Lcd.h
 #     Date: 2018/03/01
 #  Version: 1.45
 #   Device: PIC16F877A
 # Synopsis: Constants and function declarations use for the Hitachi (HD44780U)
 #           dot matrix liquid crystal display (LCD) driver.
 #
 #   Author: KALAMBAY NK
 #############################################################################*/

/*--- Global function prototypes ---------------------------------------------*/
/* Write instruction (RS = 0) or data (RS = 1) to LCD in 4-bit mode */
void LCD_send(char RS, unsigned char data);
/* Initialize the LCD - before anything else*/
void LCD_init(void);
/* Clear and home cursor on LCD */
void LCD_clear(void);
/* Move cursor to specified postion on LCD */
void LCD_goto(unsigned char x, unsigned char y);
/* Write a string of characters from ROM to LCD */
void LCD_putrs(const char *s);
/* Write a string of characters from RAM to LCD */
void LCD_puts(char *s);
/* Adds spaces infront for number string display */
void AddSpaces(unsigned char MaxLen, char StrLen);
/* Write required lenght of string characters from RAM to LCD */
void LCD_putsLen(char *s, char clen);

/*--- Global variables declarations ------------------------------------------*/
//unsigned char XXXXX;

/*--- Global Constant declarations -------------------------------------------*/
#define LCD_EN      LATDbits.LATD4
#define LCD_RS      LATDbits.LATD5
#define LCD_DATA    LATD
#define STROBE()    ((LCD_EN = 1),(LCD_EN = 0))
#define INSTR       0
#define DATA        1

/*******************************************************************************
 * Hitachi HD44780U LCD Connection Diagram
 * ----------------------------------------
 *
 *                           10   9   8   7
 *                            |   |   |   |
 *                   |--------|---|---|---|----------|
 *                   |       DB3 DB2 DB1 DB0         |  +5V
 *		     |                               |   |
 * 		     |    |---------------------|   2|---\
 *            RB3-14-|DB7 |                     |    |   /
 *            RB2-13-|DB6 |                     |   3|-->\10K
 *            RB1-12-|DB5 |	                |    |   /
 *	      RB0-11-|DB4 |---------------------|   1|---\
 *       	     |   		        |    |
 *		     |       EN R/W RS  +V  -V       |  GND
 *		     |-------|---|---|---|---|-------|
 *	      RB4-6----------|   |   |   |   |
 *            GND-5--------------|   |   |   |
 *            RB5-4------------------|   |   |
 *                15---------------------|   |
 *                16--------------------------
 * HD44780U Pin Descriptions
 * --------------------------
 *
 * 1 : VSS, Ground
 * 2 : VDD, Supply voltage +5V +/-0.4V
 * 3 : VEE, LCD contrast drive voltage
 * 4 : RS, Register select, 1=Data, 0=Instruction
 * 5 : R/W, Select read/write, 1=Read, 0=Write
 * 6 : E, Enable, 1=Enable, 0=Disable
 * 7 : DB0, Data Bus, 8-bit mode
 * 8 : DB1, Data Bus, 8-bit mode
 * 9 : DB2, Data Bus, 8-bit mode
 * 10: DB3, Data Bus, 8-bit mode
 * 11: DB4, Data Bus, 4-bit and 8-bit mode
 * 12: DB5, Data Bus, 4-bit and 8-bit mode
 * 13: DB6, Data Bus, 4-bit and 8-bit mode
 * 14: DB7, Data Bus, 4-bit and 8-bit mode
 * 15: +V Backlight (Optional)
 * 16: -V Backlight (Optional)
 *
 *******************************************************************************
 * Display Data RAM (DDRAM) Character Addresses for configured one line display
 *
 *       |_0|_____________20 Character Display____________________|19|
 * Line1 |00|01|02|03|04|05|06|07|08|09|0A|0B|0C|0D|0E|0F|10|11|12|13|
 *
 *       |20|_____________Hidden Characters_______________________|80|dec
 *       |14|.....................................................|4F|hex
 *******************************************************************************
 * Display Data RAM (DDRAM) Character Addresses for configured two line display
 *
 *       |_0|_____________20 Character Display____________________|19|
 * Line1 |00|01|02|03|04|05|06|07|08|09|0A|0B|0C|0D|0E|0F|10|11|12|13|
 * Line2 |40|41|42|43|44|45|46|47|48|49|4A|4B|4C|4D|4E|4F|50|51|52|53|
 *
 *       |20|_____________20 Hidden Characters____________________|39|dec
 *       |14|15|16|17|18|19|1A|1B|1C|1D|1E|1F|20|21|22|23|24|25|26|27|hex
 *       |54|55|56|57|58|59|5A|5B|5C|5D|5E|5F|60|61|62|63|64|65|66|67|hex
 *
 *******************************************************************************
 * Display Data RAM (DDRAM) Character Addresses for configured four line display
 *
 *       |_0|_____________20 Character Display____________________|19|
 * Line1 |00|01|02|03|04|05|06|07|08|09|0A|0B|0C|0D|0E|0F|10|11|12|13|hex
 * Line2 |40|41|42|43|44|45|46|47|48|49|4A|4B|4C|4D|4E|4F|50|51|52|53|hex
 * Line3 |14|15|16|17|18|19|1A|1B|1C|1D|1E|1F|20|21|22|23|24|25|26|27|hex
 * Line4 |54|55|56|57|58|59|5A|5B|5C|5D|5E|5F|60|61|62|63|64|65|66|67|hex
 *
 *******************************************************************************
 *
 *             	            |---|---||---|---|---|---|---|---|---|---|---------|
 *	                    |RS |R/W||DB7|DB6|DB5|DB4|DB3|DB2|DB1|DB0| Max-Time|
 *			    |---|---||---|---|---|---|---|---|---|---|---------|
 *  Clear display    	    | 0 | 0 || 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |  1.64ms |
 *			    |---|---||---|---|---|---|---|---|---|---|---------|
 *  Return home             | 0 | 0 || 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |  1.64ms |
 *			    |---|---||---|---|---|---|---|---|---|---|---------|
 *  Entry mode set 	    | 0 | 0 || 0 | 0 | 0 | 0 | 0 | 1 |I/D| S |  40us   |
 *                          |---|---||---|---|---|---|---|---|---|---|---------|
 *  Display on/off control  | 0 | 0 || 0 | 0 | 0 | 0 | 1 | D | C | B |  40us   |
 *                          |---|---||---|---|---|---|---|---|---|---|---------|
 *  Cursor or display shift | 0 | 0 || 0 | 0 | 0 | 1 |S/C|R/L| 0 | 0 |  40us   |
 *                          |---|---||---|---|---|---|---|---|---|---|---------|
 *  Function set	    | 0 | 0 || 0 | 0 | 1 |DL | N | F | 0 | 0 |  40us   |
 *                          |---|---||---|---|---|---|---|---|---|---|---------|
 *  Set CGRAM address	    | 0 | 0 || 0 | 1 |          ACG          |  40us   |
 *                          |---|---||---|---|---|---|---|---|---|---|---------|
 *  Set DDRAM address	    | 0 | 0 || 1 |            ADD            |  40us   |
 *                          |---|---||---|---|---|---|---|---|---|---|---------|
 *  Read Busy Flag & address| 0 | 1 ||BF |            AC             |  40us   |
 *                          |---|---||---|---|---|---|---|---|---|---|---------|
 *  Write to CGRAM or DDRAM | 1 | 0 ||  Write Data to DD or CG RAM   |  40us   |
 *                          |---|---||---|---|---|---|---|---|---|---|---------|
 *  Read from CGRAM or DDRAM| 1 | 1 ||  Read Data from DD or CG RAM  |  40us   |
 *                          |---|---||---|---|---|---|---|---|---|---|---------|
 *  I/D=1: Increment
 *  I/D=0: Decrement
 *  S=1  : With display shift
 *  S=0  : Without display Shift
 *  D=1  : Switch display on
 *  D=0  : Switch display off
 *  C=1  : Switch Cursor on
 *  C=0  : Switch Cursor off
 *  B=1  : Switch Blink on
 *  B=0  : Switch Blink off
 *  S/C=1: Display shift
 *  S/C=0: Cursor movement
 *  R/L=1: Shift to the right
 *  R/L=0: Shift to the left
 *  DL=0 : 4-bit interface (DB7-DB4)
 *  DL=1 : 8-bit interface (DB7-DB0)
 *  N=1  : 2 display lines
 *  N=0  : 1 display line
 *  F=1  : 5x10 dots character font
 *  F=0  : 5x8 dots character font
 *  BF=1 : Internal operation is being performed
 *  BF=0 : Instruction acceptable
 *
 *	Descriptions
 *	-----------
 *	DDRAM : Display data RAM
 *	CGRAM : Character Generator RAM
 *	ACG   : Character Generator RAM address
 *	ADD   : Display data RAM address (corresponds to cursor address)
 *	AC    : Address Counter used for both DDRAM and CGRAM
 *
 ******************************************************************************/