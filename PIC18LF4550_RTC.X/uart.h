#ifndef _UART_H
#define _UART_H
#include <stdint.h>

#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 512

#if (SERIAL_TX_BUFFER_SIZE > 256)
typedef uint16_t tx_buffer_index_t;
#else
typedef uint8_t tx_buffer_index_t;
#endif

#if (SERIAL_RX_BUFFER_SIZE > 256)
typedef uint16_t rx_buffer_index_t;
#else
typedef uint8_t rx_buffer_index_t;
#endif

volatile rx_buffer_index_t _rx_buffer_head;
volatile rx_buffer_index_t _rx_buffer_tail;
volatile tx_buffer_index_t _tx_buffer_head;
volatile tx_buffer_index_t _tx_buffer_tail;

unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];
    
void UART_Init(uint24_t baudRate);
void UART_putrs(const char * ptr);
void UART_puts(char * ptr);
uint16_t UART_available(void);
int8_t UART_peek(void);
int8_t UART_read(void);
void UART_end(void);
uint16_t UART_availableForWrite(void);
void UART_flush(void);
void UART_write(uint8_t data);
void UART_rx_complete_irq(void);
void UART_tx_udr_empty_irq(void);


#endif