/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MCP2515_H
#define	MCP2515_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#define MCP2515_CS  LATBbits.LATB3
#define MCP2515_RESET   0xC0
#define MCP2515_READ    0x03
#define DUMMY           0x00
#define MCP2515_WRITE   0x02
#define MCP2515_READ_STATUS 0xA0
#define MCP2515_RX_STATUS   0xB0
#define MCP2515_BIT_MODIFY  0x05
#define DATA_FRAME      0
#define REMOTE_FRAME    1


#define TRANSMIT_BUFFER_0   0
#define TRANSMIT_BUFFER_1   1
#define TRANSMIT_BUFFER_2   2



/*
 * address for different registers
 */

#define RXF0SIDH    0x00
#define RXF0SIDL    0x01
#define RXF0EID8    0x02
#define RXF0EID0    0x03
#define RXF1SIDH    0x04
#define RXF1SIDL    0x05
#define RXF1EID8    0x06
#define RXF1EID0    0x07
#define RXF2SIDH    0x08
#define RXF2SIDL    0x09
#define RXF2EID8    0x0A
#define RXF2EID0    0x0B
#define BFPCTRL     0x0C
#define TXRTSCTRL   0x0D
#define CANSTAT0    0x0E
#define CANCTRL0    0x0F

#define RXF3SIDH    0x10
#define RXF3SIDL    0x11
#define RRXF3EID8   0x12
#define RXF3EIID0   0x13
#define RXF4SIDH    0x14
#define RXF4SIDL    0x15
#define RXF4EID8    0x16
#define RXF4EID0    0x17
#define RXF5SIDH    0x18
#define RXF5SIDL    0x19
#define RXF5EID8    0x1A
#define RXF5EID0    0x1B
#define TEC         0x1C
#define REC         0x1D
#define CANSTAT2    0x1E
#define CANCTRL2    0x1F

#define RXM0SIDH    0x20
#define RXM0SIDL    0x21
#define RXM0EID8    0x22
#define RXM0EID0    0x23
#define RXM1SIDH    0x24
#define RXM1SIDL    0x25
#define RXM1EID8    0X26
#define RXM1EID0    0x27
#define CNF3        0x28
#define CNF2        0x29
#define CNF1        0x2A
#define CANINTE     0x2B
#define CANINTF     0x2C
#define EFLG        0x2D
#define CANSTAT3    0x2E
#define CANCTRL3    0x2F

#define TXB0CTRL    0x30
#define TXB0SIDH    0x31
#define TXB0SIDL    0x32
#define TXB0EID8    0x33
#define TXB0EID0    0x34
#define TXB0DLC     0x35
#define TXB0D0      0x36
#define TXB0D1      0x37
#define TXB0D2      0x38
#define TXB0D3      0x39
#define TXB0D4      0x3A
#define TXB0D5      0x3B
#define TXB0D6      0x3C
#define TXB0D7      0x3D
#define CANSTAT4    0x3E
#define CANCTRL     0x3F

#define TXB1CTRL    0x40
#define TXB1SIDH    0x41
#define TXB1SIDL    0x42
#define TXB1EID8    0x43
#define TXB1EID0    0x44
#define TXB1DLC     0x45
#define TXB1D0      0x46
#define TXB1D1      0x47
#define TXB1D2      0x48
#define TXB1D3      0x49
#define TXB1D4      0x4A
#define TXB1D5      0x4B
#define TXB1D6      0x4C
#define TXB1D7      0x4D
#define CANSTAT5    0x4E
#define CANCTRL5    0x4F

#define TXB2CTRL    0x50
#define TXB2SIDH    0x51
#define TXB2SIDL    0x52
#define TXB2EID8    0x53
#define TXB2EID0    0x54
#define TXB2DLC     0x55
#define TXB2D0      0x56
#define TXB2D1      0x57
#define TXB2D2      0x58
#define TXB2D3      0x59
#define TXB2D4      0x5A
#define TXB2D5      0x5B
#define TXB2D6      0x5C
#define TXB2D7      0x5D
#define CANSTAT6    0x5E
#define CANCTRL6    0x5F

#define RXB0CTRL    0x60
#define RXB0SIDH    0x61
#define RXB0SIDL    0x62
#define RXB0EID8    0x63
#define RXB0EID0    0x64
#define RXB0DLC     0x65
#define RXB0D0      0x66
#define RXB0D1      0x67
#define RXB0D2      0x68
#define RXB0D3      0x69
#define RXB0D4      0x6A
#define RXB0D5      0x6B
#define RXB0D6      0x6C
#define RXB0D7      0x6D
#define CANSTAT7    0x6E
#define CANCTRL7    0x6F

#define RXB1CTRL    0x70
#define RXB1SIDH    0x71
#define RXB1SIDL    0x72
#define RXB1EID8    0x73
#define RXB1EID0    0x74
#define RXB1DLC     0X75
#define RXB1D0      0x76
#define RXB1D1      0x77
#define RXB1D2      0x78
#define RXB1D3      0x79
#define RXB1D4      0x7A
#define RXB1D5      0x7B
#define RXB1D6      0x7C
#define RXB1D7      0x7D
#define CANSTAT8    0x7E
#define CANCTRL8    0x7F

/*
 * Determine the bits
 */

#define BIT0        0b00000001 
#define BIT1        0b00000010
#define BIT2        0b00000100
#define BIT3        0b00001000
#define BIT4        0b00010000
#define BIT5        0b00100000
#define BIT6        0b01000000
#define BIT7        0b10000000
typedef uint8_t U8; 

#define ID_FOR_TEMP 0b10101010101
#define ID_FOR_POT  0b00110011001
#define ID_EX_FOR_TEMP  0b00000000000000000000000001111
#define ID_EX_FOR_POT   0b00000000000000000000000000111

void MCP2515_Init(void);
static void MCP2515_reset(void);
void MCP2515_write(const uint8_t data, const uint8_t address);
uint8_t MCP2515_read(const uint8_t address);
void CONFIG_REGISTER(const uint8_t addr, const uint8_t msk, const uint8_t dt);
void MCP2515_transmitStand(U8 dtLen, uint16_t msgID, const U8 * ptr, U8 buf, U8 RTR);
void MCP2515_transmitExt(U8 dtLen, uint32_t address, const U8 * ptr, U8 buf, U8 RTR);
void MCP2515_bulkSend(const U8 * dt, const uint8_t addr, U8 size);// send bulk data
#endif	/* XC_HEADER_TEMPLATE_H */

