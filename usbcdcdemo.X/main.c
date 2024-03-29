#include "sysconfig.h"

#include <xc.h>

#include "main.h"
#include "usb_cdc_lib.h"

void main(void) 
{
    initUSBLib();
    
    // TODO: Initializing routines.   
    
    while(1)
    {
        // TODO: Main service loop.
        
        // *********************** Sample echo routine ***********************
        //putUSBUSART("Hello World\r\n", 13);
        
        if(isUSBReady())
        {
            uint8_t i;
            uint8_t numBytesRead;
            numBytesRead = getsUSBUSART(usbReadBuffer, sizeof(usbReadBuffer));
            for(i = 0; i< numBytesRead; i++)
            {
                switch(usbReadBuffer[i])
                {
                    /* echo line feeds and returns without modification. */
                    case 0x0A:
                    case 0x0D:
                        usbWriteBuffer[i] = usbReadBuffer[i];
                        break;
                    default:
                        usbWriteBuffer[i] = usbReadBuffer[i];
                        break;
                }
            }
            
            putUSBUSART("Hello World\r\n", 13); 
            __delay_ms(100); 
            if(numBytesRead > 0)
            {
                putUSBUSART(usbWriteBuffer,numBytesRead);
            }
        }
        
        // *******************************************************************
        
        CDCTxService();
    }
    
    return;
}

void __interrupt() mainISR (void)
{
    processUSBTasks();
    
    // TODO: Place interrupt handlers related to other peripherals.
}