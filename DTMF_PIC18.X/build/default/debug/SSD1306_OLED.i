# 1 "SSD1306_OLED.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/kolel/.mchp_packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "SSD1306_OLED.c" 2
# 1 "./SSD1306.h" 1
# 19 "./SSD1306.h"
# 1 "./fonts.h" 1
# 42 "./fonts.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 2 3






# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\features.h" 1 3
# 10 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 2 3
# 25 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 122 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 168 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 204 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 411 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 25 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 2 3


void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);
# 65 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 3
char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 42 "./fonts.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stdint.h" 1 3
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 127 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 142 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 158 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;
# 173 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int32_t;





typedef long long int64_t;
# 188 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;
# 209 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 229 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 144 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 144 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stdint.h" 2 3
# 43 "./fonts.h" 2
# 54 "./fonts.h"
typedef struct {
 uint8_t FontWidth;
 uint8_t FontHeight;
 const uint16_t *data;
} FontDef_t;




typedef struct {
 uint16_t Length;
 uint16_t Height;
} FONTS_SIZE_t;
# 81 "./fonts.h"
extern FontDef_t Font_7x10;




extern FontDef_t Font_11x18;




extern FontDef_t Font_16x26;
# 110 "./fonts.h"
char* FONTS_GetStringSize(char* str, FONTS_SIZE_t* SizeStruct, FontDef_t* Font);
# 19 "./SSD1306.h" 2

typedef enum {
 SSD1306_COLOR_BLACK = 0x00,
 SSD1306_COLOR_WHITE = 0x01
} SSD1306_COLOR_t;
# 38 "./SSD1306.h"
uint8_t SSD1306_Init(void);

void SSD1306_UpdateScreen(void);







void SSD1306_ToggleInvert(void);







void SSD1306_Fill(SSD1306_COLOR_t Color);
# 66 "./SSD1306.h"
void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);







void SSD1306_GotoXY(uint16_t x, uint16_t y);
# 84 "./SSD1306.h"
char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color);
# 94 "./SSD1306.h"
char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);
# 106 "./SSD1306.h"
void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c);
# 118 "./SSD1306.h"
void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
# 130 "./SSD1306.h"
void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
# 144 "./SSD1306.h"
void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);
# 155 "./SSD1306.h"
void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);
# 166 "./SSD1306.h"
void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);
# 181 "./SSD1306.h"
void ssd1306_I2C_Init();
# 191 "./SSD1306.h"
void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
# 202 "./SSD1306.h"
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);
# 213 "./SSD1306.h"
void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);



void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row);


void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row);


void SSD1306_Scrolldiagright(uint8_t start_row, uint8_t end_row);


void SSD1306_Scrolldiagleft(uint8_t start_row, uint8_t end_row);



void SSD1306_Stopscroll(void);




void SSD1306_InvertDisplay (int i);

void I2C_Master_Transmit(uint8_t addr, uint8_t * dt, uint16_t count);






void SSD1306_Clear (void);

void SSD1306_WRITECOMMAND(uint8_t value);
# 1 "SSD1306_OLED.c" 2

# 1 "./I2C.h" 1
# 15 "./I2C.h"
void I2C_INTIALIZE(uint24_t clock);
void I2C_start(void);
void I2C_stop(void);
void I2C_RS(void);
char I2C_read(uint8_t ACK_NACK);
void I2C_Write(uint8_t data);
void I2C_scanBus(void);
void I2C_clrBuf(void);
# 2 "SSD1306_OLED.c" 2



typedef struct {
 uint16_t CurrentX;
 uint16_t CurrentY;
 uint8_t Inverted;
 uint8_t Initialized;
} SSD1306_t;


static SSD1306_t SSD1306;

uint8_t SSD1306_Buffer[128 * 64 / 8];
uint8_t SSD1306_Init(void) {

    SSD1306_WRITECOMMAND(0xAE);
    SSD1306_WRITECOMMAND(0x20);
    SSD1306_WRITECOMMAND(0x10);
    SSD1306_WRITECOMMAND(0xB0);
    SSD1306_WRITECOMMAND(0xC8);
    SSD1306_WRITECOMMAND(0x00);
    SSD1306_WRITECOMMAND(0x10);
    SSD1306_WRITECOMMAND(0x40);
    SSD1306_WRITECOMMAND(0x81);
    SSD1306_WRITECOMMAND(0xFF);
    SSD1306_WRITECOMMAND(0xA1);
    SSD1306_WRITECOMMAND(0xA6);
    SSD1306_WRITECOMMAND(0xA8);
    SSD1306_WRITECOMMAND(0x3F);
    SSD1306_WRITECOMMAND(0xA4);
    SSD1306_WRITECOMMAND(0xD3);
    SSD1306_WRITECOMMAND(0x00);
    SSD1306_WRITECOMMAND(0xD5);
    SSD1306_WRITECOMMAND(0xF0);
    SSD1306_WRITECOMMAND(0xD9);
    SSD1306_WRITECOMMAND(0x22);
    SSD1306_WRITECOMMAND(0xDA);
    SSD1306_WRITECOMMAND(0x12);
    SSD1306_WRITECOMMAND(0xDB);
    SSD1306_WRITECOMMAND(0x20);
    SSD1306_WRITECOMMAND(0x8D);
    SSD1306_WRITECOMMAND(0x14);
    SSD1306_WRITECOMMAND(0xAF);


    SSD1306_WRITECOMMAND(0x2E);


    SSD1306_Fill(SSD1306_COLOR_BLACK);


    SSD1306_UpdateScreen();


    SSD1306.CurrentX = 0;
    SSD1306.CurrentY = 0;


    SSD1306.Initialized = 1;
    return 1;
}

void SSD1306_WRITECOMMAND(uint8_t value)
{
    I2C_start();
    I2C_Write(0x78);
    I2C_Write(0x00);
    I2C_Write(value);
    I2C_stop();
}

void SSD1306_Fill(SSD1306_COLOR_t color) {

 memset(SSD1306_Buffer, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer));
}
void SSD1306_UpdateScreen(void) {
 uint8_t m;

 for (m = 0; m < 8; m++) {
  SSD1306_WRITECOMMAND(0xB0 + m);
  SSD1306_WRITECOMMAND(0x00);
  SSD1306_WRITECOMMAND(0x10);


  ssd1306_I2C_WriteMulti(0x78, 0x40, &SSD1306_Buffer[128 * m], 128);
 }
}

void SSD1306_GotoXY(uint16_t x, uint16_t y) {

 SSD1306.CurrentX = x;
 SSD1306.CurrentY = y;
}

char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color) {

 while (*str) {

  if (SSD1306_Putc(*str, Font, color) != *str) {

   return *str;
  }


  str++;
 }


 return *str;
}

char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color) {
 uint32_t i, b, j;


 if (
  128 <= (SSD1306.CurrentX + Font->FontWidth) ||
  64 <= (SSD1306.CurrentY + Font->FontHeight)
 ) {

  return 0;
 }


 for (i = 0; i < Font->FontHeight; i++) {
  b = Font->data[(ch - 32) * Font->FontHeight + i];
  for (j = 0; j < Font->FontWidth; j++) {
   if ((b << j) & 0x8000) {
    SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t) color);
   } else {
    SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t)!color);
   }
  }
 }


 SSD1306.CurrentX += Font->FontWidth;


 return ch;
}

void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color)
{
 if (
  x >= 128 ||
  y >= 64
 ) {

  return;
 }


 if (SSD1306.Inverted) {
  color = (SSD1306_COLOR_t)!color;
 }


 if (color == SSD1306_COLOR_WHITE) {
  SSD1306_Buffer[x + (y / 8) * 128] |= 1 << (y % 8);
 } else {
  SSD1306_Buffer[x + (y / 8) * 128] &= ~(1 << (y % 8));
 }
}

void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
    uint8_t dt[256];
    dt[0] = reg;
    uint8_t i;
    for (i = 0; i < count; i++)
        dt[i + 1] = data[i];

    I2C_Master_Transmit(address, dt, count + 1);

}

void I2C_Master_Transmit(uint8_t addr, uint8_t * dt, uint16_t count)
{
    I2C_start();
    I2C_Write(addr);
    for(uint16_t x = 0; x <(count); x++)
    {
        I2C_Write(*dt++);
    }
    I2C_stop();
}

void SSD1306_Clear (void)
{
 SSD1306_Fill(0);
    SSD1306_UpdateScreen();
}
