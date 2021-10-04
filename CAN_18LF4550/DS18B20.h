/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
 
#ifndef DS18B20_H
#define	DS18B20_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#define _XTAL_FREQ  16000000UL
#define WAIT()  __delay_us(100)
#define Delay5us()  __delay_us(5)
#define PIN_IN_OR_OUT   TRISBbits.TRISB3
#define PIN     LATDbits.LATD5
void DS13B20_Init(void);
uint8_t DS18B20_read(void);
static void BitBangWrite(uint8_t byte);
static uint8_t BitbangRead(void);
static void SetAsInput(void);
static void Setasoutput(void);



#endif	/* XC_HEADER_TEMPLATE_H */

