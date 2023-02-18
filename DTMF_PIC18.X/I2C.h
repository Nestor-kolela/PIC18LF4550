/* 
 * File:   i2c.h
 * Author: CEDRIC
 *
 * Created on 25 April 2020, 7:05 PM
 */

#ifndef I2C_H
#define	I2C_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif

void I2C_INTIALIZE(uint24_t clock);
void I2C_start(void);
void I2C_stop(void);
void I2C_RS(void);
char I2C_read(uint8_t ACK_NACK); 
void I2C_Write(uint8_t data);
void I2C_scanBus(void);
void I2C_clrBuf(void);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */