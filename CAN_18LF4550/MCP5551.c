/*
 * File:   MCP5551.c
 * Author: Nestor
 *
 * Created on December 2, 2020, 7:19 PM
 */


#include "SPI.h"
#include "MCP2515.h"
#define _XTAL_FREQ  16000000

   

void MCP2515_Init(void)
{
#if 1
    MCP2515_reset(); //reset the module
    __delay_ms(10);
    //When it is in configuration mode
    //then set the following registers
    //CNF1, CNF2, CNF3
    //TXRTSCTRL
    //Filter registers
    //Mask registers
    
    for(uint8_t cnt = 0; cnt < 14; cnt++)
    {
        MCP2515_write(0x00, TXB0CTRL + cnt); //fill all of these with zeros
    }
    
    for(uint8_t cnt = 0; cnt < 14; cnt++)
    {
        MCP2515_write(0x00, TXB1CTRL + cnt);
    }
    
    for(uint8_t cnt = 0; cnt < 14; cnt++)
    {
        MCP2515_write(0x00, TXB2CTRL + cnt);
    }
    
    for(uint8_t cnt = 0; cnt < 8; cnt++)
    {
        MCP2515_write(0x00, RXM0SIDH + cnt);
    }
    
    CONFIG_REGISTER(CANINTE, 0b10100011, 0xFF); //enable interrupts for 
    //receive RX0IF, RX1IF, ERROR ON TRANSMISSION AND MESSAGE ERROR interrupt enable
    
    //receive all valid messages using standard or extended identifiers
    //that meet the filter criteria
    //RXF0 is applied for RXB0
    //RXF1 is applied for RXB1
    
    MCP2515_write(0b01100100, RXB0CTRL);
    
    MCP2515_write(0b01100000, RXB1CTRL);
        
    //set the baud rate
    CONFIG_REGISTER(CNF1, 0x04, 0xFF); // CNF1
    CONFIG_REGISTER(CNF2, 0b11111001, 0xFF); // CNF2
    CONFIG_REGISTER(CNF3, 0b00000100, 0xFF); //CNF3
    CONFIG_REGISTER(CANINTE, 0xFF, 0xFF);
    
#endif
    
    
#if 0
    //here you must configure the mask and filters 
    
    CONFIG_REGISTER(RXM0SIDH, 0x00, 0xFF);
    CONFIG_REGISTER(RXM0SIDL, 0b11100000, 0xFF);
    
    CONFIG_REGISTER(RXM1SIDH, 0x00, 0xFF);
    CONFIG_REGISTER(RXM1SIDL, 0b11100000, 0xFF);
    
    CONFIG_REGISTER(RXF0SIDH, 0b10101010, 0xFF);
    CONFIG_REGISTER(RXF0SIDL, 0b10100000, 0xFF);
    
    CONFIG_REGISTER(RXF1SIDH, 0b10101010, 0xFF);
    CONFIG_REGISTER(RXF1SIDL, 0b10100000, 0xFF);
    
    CONFIG_REGISTER(RXF2SIDH, 0b10101010, 0xFF);
    CONFIG_REGISTER(RXF2SIDL, 0b10100000, 0xFF);
    
    CONFIG_REGISTER(RXF3SIDH, 0b10101010, 0xFF);
    CONFIG_REGISTER(RXF3SIDL, 0b10100000, 0xFF);
    
    CONFIG_REGISTER(RXF4SIDH, 0b10101010, 0xFF);
    CONFIG_REGISTER(RXF4SIDL, 0b10100000, 0xFF);
    
    CONFIG_REGISTER(RXF5SIDH, 0b10101010, 0xFF);
    CONFIG_REGISTER(RXF5SIDL, 0b10100000, 0xFF);
    
#endif

    MCP2515_write(0b00000111, CANCTRL0); //normal mode
    
    __delay_ms(1000);
    
    //CONFIG canintf
    //config RX0
}//END MCP2515_Init

void MCP2515_write(const uint8_t data, const uint8_t address)
{
    MCP2515_CS = 0;
    SPI_putc(MCP2515_WRITE);
    SPI_putc(address);
    SPI_putc(data);
    MCP2515_CS = 1;
}//end MCP2515_Write

void MCP2515_bulkSend(const U8 * dt, const uint8_t addr, U8 size)
{
    MCP2515_CS = 0;
    SPI_putc(MCP2515_WRITE);
    SPI_putc(addr);
    
    for(U8 tempValue = 0; tempValue < size; tempValue++)
    {
        SPI_putc(*(dt + tempValue));
    }
    MCP2515_CS = 1;
}//end MCP2515_bulkSend
uint8_t MCP2515_read(const uint8_t address)
{
    uint8_t dataRead;
    MCP2515_CS = 0;
    SPI_putc(MCP2515_READ);
    SPI_putc(address);
    dataRead = SPI_putc(DUMMY); //
    MCP2515_CS = 1;
    return dataRead;
}//end MCP2515_read

static void MCP2515_reset(void)
{
    MCP2515_CS = 0; //clear it
    SPI_putc(MCP2515_RESET);
    MCP2515_CS = 1;
}//reset the MCP2515 upon reset

void CONFIG_REGISTER(const uint8_t addr, const uint8_t msk, const uint8_t dt)
{
    MCP2515_CS = 0;
    SPI_putc(MCP2515_BIT_MODIFY);
    SPI_putc(addr);
    SPI_putc(msk);
    SPI_putc(dt);
    MCP2515_CS = 1;
}//wait

void MCP2515_send(const uint8_t idLen)
{
    if(idLen==0)
    {
        //MCP2515_transmitStand(); //transmit standard data
    }else
    {
        //MCP2515_transmitExt(); //transmit extended data
    }
}

void MCP2515_transmitStand(U8 dtLen, uint16_t msgID, const U8 * ptr, U8 buf, U8 RTR)
{
    //uint8_t tempValue = 0;
    switch(buf)
    {
        case 0: //if buf is zero then use the 0 buffer
        {
            MCP2515_write((uint8_t ) msgID >> 3, TXB0SIDH);
            MCP2515_write((uint8_t) msgID << 5, TXB0SIDL);
            if(RTR==0)
            {
                MCP2515_write(dtLen, TXB0DLC); 
            }else
            {
                MCP2515_write(dtLen | 0b01000000, TXB0DLC); 
            }//end RTR == 0
            //void MCP2515_bulkSend(const U8 * dt, const uint8_t addr, U8 size);// send bulk data
            MCP2515_bulkSend(ptr, TXB0D0, dtLen);
            //static void CONFIG_REGISTER(const uint8_t addr, const uint8_t msk, const uint8_t dt)
            CONFIG_REGISTER(TXB0CTRL, 0xFF, 0x08);  //start transmission
            //tempValue = MCP2515_read(TXB0CTRL_ADDRESS);
            
        }//end case
            break;
            
        case 1://if buf is 1 then use buffer 1
        {
            MCP2515_write((uint8_t ) msgID >> 3, TXB1SIDH);
            MCP2515_write((uint8_t) msgID << 5, TXB1SIDL);
            if(RTR==0)
            {
                MCP2515_write(dtLen, TXB1DLC); 
            }else
            {
                MCP2515_write(dtLen | 0b01000000, TXB1DLC); 
            } //END RTC==0
            MCP2515_bulkSend(ptr, TXB1D0, dtLen);
            CONFIG_REGISTER(TXB1CTRL, 0xFF, 0x08); //start transmition
            //tempValue = MCP2515_read(TXB1CTRL_ADDRESS);
        }// case 1
            break;
        case 2: //if buf is 2 then use buffer 2
        {
            MCP2515_write((uint8_t ) msgID >> 3, TXB2SIDH);
            MCP2515_write((uint8_t) msgID << 5, TXB2SIDL);
            if(RTR==0)
            {
                MCP2515_write(dtLen, TXB2DLC); 
            }else
            {
                MCP2515_write(dtLen | 0b01000000, TXB2DLC); 
            }// end RTC==0
            MCP2515_bulkSend(ptr, TXB2D0, dtLen);
            CONFIG_REGISTER(TXB2CTRL, 0xFF, 0x08);
            //tempValue = MCP2515_read(TXB2CTRL_ADDRESS);
        } //case 2
            break;
        default:
        {
            //or do nothing
        }break;
    }
}
void MCP2515_transmitExt(U8 dtLen, uint32_t address, const U8 * ptr, U8 buf, U8 RTR)
{
    //0b1 1111 1111 1111 1111 1111 1111 1111
    //0b00
    //
    switch(buf)
    {
        case 0:
        {
            MCP2515_write((uint8_t) address >> 3, TXB0SIDH);
            MCP2515_write((uint8_t) ((address << 5) | (0x08) | (address >> 27)), TXB0SIDL); //sending extended identifier
            MCP2515_write((uint8_t) (address >> 19), TXB0EID8);
            MCP2515_write((uint8_t) (address >> 11), TXB0EID0);
            if(RTR==0)
            {
                MCP2515_write(dtLen, TXB0DLC); 
            }else
            {
                MCP2515_write(dtLen | 0b01000000, TXB0DLC); 
            }
            MCP2515_bulkSend(ptr, TXB0D0, dtLen);
            CONFIG_REGISTER(TXB0CTRL, 0xFF, 0x08);
        }break;
        
        case 1:
        {
            MCP2515_write((uint8_t) address >> 3, TXB1SIDH);
            MCP2515_write((uint8_t) ((address << 5) | (0x08) | (address >> 27)), TXB1SIDL); //sending extended identifier
            MCP2515_write((uint8_t) (address >> 19), TXB1EID8);
            MCP2515_write((uint8_t) (address >> 11), TXB1EID0);
            if(RTR==0)
            {
                MCP2515_write(dtLen, TXB1DLC); 
            }else
            {
                MCP2515_write(dtLen | 0b01000000, TXB1DLC); 
            }
            MCP2515_bulkSend(ptr, TXB1D0, dtLen);
            CONFIG_REGISTER(TXB1CTRL, 0xFF, 0x08);
            
        }break;
        
        case 2:
        {
            MCP2515_write((uint8_t) address >> 3, TXB2SIDH);
            MCP2515_write((uint8_t) ((address << 5) | (0x08) | (address >> 27)), TXB2SIDL); //sending extended identifier
            MCP2515_write((uint8_t) (address >> 19), TXB2EID8);
            MCP2515_write((uint8_t) (address >> 11), TXB2EID0);
            if(RTR==0)
            {
                MCP2515_write(dtLen, TXB2DLC); 
            }else
            {
                MCP2515_write(dtLen | 0b01000000, TXB2DLC); 
            }
            MCP2515_bulkSend(ptr, TXB2D0, dtLen);
            CONFIG_REGISTER(TXB2CTRL, 0xFF, 0x08);
            
        }break;
        default:
        {
            
        }break; //do nothing if the proper buffer is not passed
    }
}

