/*
 * File:   SPI.c
 * Author: Nestor
 *
 * Created on November 21, 2020, 9:16 PM
 */


#include <xc.h>
#define _XTAL_FREQ  16000000
#define     latch_Data()    Shift_data();  
void SPI_Init(void){ 
    
    /* Input data is sampled at the end of data output time
     * output data is shifted out on the rising edge of SCK
     */
    
    TRISCbits.TRISC7 = 0;
    
    TRISAbits.TRISA5 = 1;
    
    TRISBbits.RB1 = 0;
    
    TRISDbits.RD0 = 0;
    
    SSPSTAT=0xC0;
    /* Master mode
     * Clock is 4 MHz
     * Set the polarity to idle low
     */
    SSPCON1=0x20; 
    
    /* TRISC4 should have been an input but 
     * since the input is not used in this case
     * therefore disable it by setting it as an output
     */
    
    
}
unsigned char SPI_putc(unsigned char data){
    SSPBUF=data; //write data to buffer
    while(!SSPSTATbits.BF); //wait until transmission is complete
    return SSPBUF;
}

void SPI_putrs(const unsigned char *data) {
    while (*data) 
        SPI_putc(*(data++));
}

void SPI_puts(unsigned char *data) {
    while (*data)
        SPI_putc(*(data++));
}

