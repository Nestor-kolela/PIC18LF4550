/*
 * File:   keypad.c
 * Author: kolel
 *
 * Created on 15 February 2023, 5:27 PM
 */


#include "keypad.h"
#include <stdbool.h>
void Keypad_Init(void)
{
    //Set as inputs... 
    COLUMN1_DIR = 1; 
    COLUMN1_DIR = 1;
    COLUMN1_DIR = 1;
    COLUMN1_DIR = 1;
    
    //Set as outputs... 
    
    ROW1_DIR = 0; 
    ROW2_DIR = 0;
    ROW3_DIR = 0;
    ROW4_DIR = 0;
    
    ROW1 = 1; 
    ROW2 = 1;
    ROW3 = 1;
    ROW4 = 1;
}
#define RowA    ROW1
#define RowB    ROW2
#define RowC    ROW3
#define RowD    ROW4

#define C1      COLUMN1
#define C2      COLUMN2
#define C3      COLUMN3
#define         Buzzer()
#define C4      COLUMN4

#define Keypad_Delay()      __delay_ms(50)
#define KEYPAD_KEY_DELAY()  __delay_us(1);
//#define HANDLE_INV_BIT      true
int8_t Keypad_Sample(void)
{
#if defined(HANDLE_INV_BIT)
    RowA=0;
    RowB=1;
    RowC=1;
    RowD=1;
#else 
    PORTD |= 0xFF; 
    RowA = 0; 
    KEYPAD_KEY_DELAY(); 
#endif
    if(C1 == 0){
        Keypad_Delay();
        while(C1==0);
        Buzzer();
        return '1';
    }
    if(C2 == 0){
        Keypad_Delay();
        while(C2==0);
        Buzzer();
        return '2';
    }
    if(C3 == 0){
        Keypad_Delay();
        while(C3==0);
        Buzzer();
        return '3';
    }
    if(C4 == 0){
        Keypad_Delay();
        while(C4==0);
        Buzzer();
        return 'A';
    }
#if defined(HANDLE_INV_BIT)
    RowA=1;
    RowB=0;
    RowC=1;
    RowD=1;
#else
    PORTD |= 0xFF; 
    RowB = 0; 
    KEYPAD_KEY_DELAY(); 
#endif
    
    if(C1 == 0)
    {
        Keypad_Delay(); 
        while(C1==0);
        Buzzer();
        return '4';
    }
    if(C2 == 0){
        Keypad_Delay(); 
        while(C2==0);
        Buzzer();
        return '5';
    }
    if(C3 == 0){
        Keypad_Delay();
        while(C3==0);
        Buzzer();
        return '6';
    }
    
    if(C4 == 0){
        Keypad_Delay();
        while(C4==0);
        Buzzer();
        return 'B';
    }

        #if defined(HANDLE_INV_BIT)
    RowA=1;
    RowB=1;
    RowC=0;
    RowD=1;
#else
    PORTD |= 0xFF; 
    RowC = 0;
    KEYPAD_KEY_DELAY(); 
#endif
    
    if(C1 == 0)
    {
        Keypad_Delay();
        while(C1==0);
        Buzzer();
        return '7';
    }
    if(C2 == 0)
    {
        Keypad_Delay();
        while(C2 == 0);
        Buzzer();
        return '8';
    }
    if(C3 == 0)
    {
        Keypad_Delay();
        while(C3 == 0);
        Buzzer();
        return '9';
    }
    
    if(C4 == 0)
    {
        Keypad_Delay();
        while(C4 == 0);
        Buzzer();
        return 'C';
    }
    
#if defined(HANDLE_INV_BIT)
    RowA=1;
    RowB=1;
    RowC=1;
    RowD=0;
#else
    PORTD |= 0xFF; 
    RowD = 0;
    KEYPAD_KEY_DELAY();
#endif
    
    if(C1 == 0){
        Keypad_Delay();
        while(C1 == 0);
        Buzzer();
        return '*';
    }
    if(C2 == 0){
        Keypad_Delay();
        while(C2 == 0);
        Buzzer();
        return '0';
    }
    if(C3 == 0){
        Keypad_Delay();
        while(C3 == 0);
        Buzzer();
        return '#';
    }
    if(C4 == 0)
    {
        Keypad_Delay();
        while(C4 == 0);
        Buzzer();
        return 'D';
    }
   
    return -1;
}
/*
int8_t Keypad_Sample(void)
{
    if(COLUMN1 && COLUMN2 && COLUMN3 && COLUMN4)
    {
        //no button pressed... 
        return - 1; 
    }else
    {
        // 
        __delay_ms(20); 
        if(COLUMN1 && COLUMN2 && COLUMN3 && COLUMN4)
        {
            return - 1; 
        }else
        {
            // 
            PORTD |= 0xFF; 
            ROW1 = 0; 
            
            if(!ROW1)
            {
                return (int8_t) '1'; 
            }
            
            if(!ROW2)
            {
                return (int8_t) '2'; 
            }
            
            if(!ROW3)
            {
                return (int8_t) '3'; 
            }
            
            if(!ROW4)
            {
                return (int8_t) 'A'; 
            }
            
            PORTD |= 0xFF; 
            ROW2 = 0; 
            
            if(!(ROW1))
            {
                return (int8_t) '4'; 
            }
            
            if(!(ROW2))
            {
                return (int8_t) '5'; 
            }
            
            if(!(ROW3))
            {
                return (int8_t) '6'; 
            }
            
            if(!(ROW4))
            {
                return (int8_t) 'B'; 
            }
            
            PORTD |= 0xFF; 
            ROW3 = 0; 
            
            if(!(ROW1))
            {
                return (int8_t) '7'; 
            }
            
            if(!(ROW2))
            {
                return (int8_t) '8'; 
            }
            
            if(!(ROW3))
            {
                return (int8_t) '9'; 
            }
            
            if(!(ROW4))
            {
                return (int8_t) 'C'; 
            }
            
            PORTD |= 0xFF; 
            ROW4 = 0; 
            
            if(!(ROW1))
            {
                return (int8_t) '*'; 
            }
            
            if(!(ROW2))
            {
                return (int8_t) '0'; 
            }
            
            if(!(ROW3))
            {
                return (int8_t) '#'; 
            }
            
            if(!(ROW4))
            {
                return (int8_t) 'D'; 
            }
        }
    }
}

 * */