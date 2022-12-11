

#include <xc.h>

#include "uart.h"
volatile rx_buffer_index_t _rx_buffer_head;
volatile rx_buffer_index_t _rx_buffer_tail;
volatile tx_buffer_index_t _tx_buffer_head;
volatile tx_buffer_index_t _tx_buffer_tail;

unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

#define _XTAL_FREQUENCY  48000000UL

void UART_Init(uint24_t baudRate) {
    _rx_buffer_head = 0;
    _rx_buffer_tail = 0;
    _tx_buffer_head = 0;
    _tx_buffer_tail = 0;
    uint16_t temp = 0;
    TXSTA = 0b00100100; //
    BAUDCON = 0b00001000;

    if(!(TXSTAbits.SYNC) && !(BAUDCONbits.BRG16) && !(TXSTAbits.BRGH))
    {
        SPBRG = (uint8_t)((_XTAL_FREQUENCY) / (baudRate * 64)) - 1;
    }
    else if(!(TXSTAbits.SYNC) && !(BAUDCONbits.BRG16) && (TXSTAbits.BRGH))
    {
        temp = (uint8_t)(((_XTAL_FREQUENCY) / (baudRate * 16)) - 1);
        SPBRGH = (uint8_t)((temp & 0xFF00) >> 8);
        SPBRG = (uint8_t) (temp & 0x00FF);
    }else if(!(TXSTAbits.SYNC) && (BAUDCONbits.BRG16) && (TXSTAbits.BRGH))
    {
        temp = (uint8_t)(((_XTAL_FREQUENCY) / (baudRate * 4)) - 1);
        SPBRGH = (uint8_t)((temp & 0xFF00) >> 8);
        SPBRG = (uint8_t) (temp & 0x00FF);
    }
    RCSTA = 0b10010000; 
    
    /*
     * COnfigure the function pointer for the interrupt on reception
     */
    
    PIE1bits.RCIE = 1; //enable reception
    IPR1bits.RCIP = 1; //high priority
    IPR1bits.TX1IP = 1; //make it high priority
}



void UART_putrs(const char * ptr)
{
    while(*ptr)
    {
        UART_write(*ptr++);
    }
}
void UART_puts(char * ptr)
{
    while(*ptr)
    {
        UART_write(*ptr++);
    }
    
}

uint16_t UART_available(void) 
{
    return ((uint16_t) (SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}
int8_t UART_peek(void) 
{
    if (_rx_buffer_head == _rx_buffer_tail) {
        return -1;
    } else {
        return (int8_t)_rx_buffer[_rx_buffer_tail];
    }
    
}
int8_t UART_read(void) {
    // if the head isn't ahead of the tail, we don't have any characters
    if (_rx_buffer_head == _rx_buffer_tail) {
        return -1;
    } else {
        unsigned char c = _rx_buffer[_rx_buffer_tail];
        _rx_buffer_tail = (rx_buffer_index_t) (_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
        return (int8_t)c;
    }
}
void UART_end(void)
{
    //call flush function
    
    //clear rx receiver interrupt
    
    // clear tx enable
    
    //and so on
}
uint16_t UART_availableForWrite(void) {
    tx_buffer_index_t head;
    tx_buffer_index_t tail;

    head = _tx_buffer_head;
    tail = _tx_buffer_tail;
    
    if (head >= tail) return SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
    return tail - head - 1;
    
}
void UART_flush(void)
{
    
    
}
void UART_write(uint8_t data) {
    tx_buffer_index_t i = (_tx_buffer_head + 1) % SERIAL_TX_BUFFER_SIZE;
    while (i == _tx_buffer_tail);
    _tx_buffer[_tx_buffer_head] = data;
    _tx_buffer_head = i;
    PIE1bits.TX1IE = 1; //enable this to start the interrupt
    return ;
    
}
void UART_rx_complete_irq(void) {
    uint8_t c;
    if (RCSTAbits.OERR) {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    if (RCSTAbits.FERR) {
        //buffer[arrayIndex++]=RCREG;
        //read
        c = RCREG;
    }
    c = RCREG;
    rx_buffer_index_t i = (unsigned int) (_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;
    if (i != _rx_buffer_tail) 
    {
        _rx_buffer[_rx_buffer_head] = c;
        _rx_buffer_head = i;
    } else {
        RCREG; //read it still
    }

    //end if for UART receive reception

}
void UART_tx_udr_empty_irq(void)
{
    uint8_t c = _tx_buffer[_tx_buffer_tail];
    _tx_buffer_tail = (_tx_buffer_tail + 1) % SERIAL_TX_BUFFER_SIZE;
    TXREG = c;
    if(_tx_buffer_head == _tx_buffer_tail)
    {
        //disable the interrupt for transmission
        //UCA0IE &= ~(UCTXIE); //disable interrupts
        PIE1bits.TX1IE = 0; //turn the interrupt off
    }
}