#ifndef	_OLED_H_
#define _OLED_H_

/*#define RESET  PTC12_OUT
#define DC     PTC10_OUT
#define D1     PTC14_OUT
#define D0     PTC16_OUT//这部分宏定义在data.h*/

 typedef unsigned char byte;
 typedef unsigned int word;
 extern byte beyond96x64[512];
 void OLED_WrDat(uint8 data);
 void OLED_Set_Pos(byte x, byte y);
 void OLED_Init(void);
 void OLED_CLS(void);
 void OLED_P8x16Str(byte x,byte y,byte ch[]);
 void OLED_P14x16Str(byte x,byte y,byte ch[]);
 void OLED_Print(byte x, byte y, byte ch[]);
 void OLED_PutPixel(byte x,byte y);
 void OLED_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
 void OLED_Fill(byte dat);
 void Display(int16 i,uint8 x,uint8 y);
 void DisplayFloat(int16 i,uint8 x,uint8 y);
#endif