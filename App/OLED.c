#include "include.h"
#include "OLED.h"
#include "OLED_Fonts.h"

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		  64
#define	Brightness	0xCF 



#define X_WIDTH 128
#define Y_WIDTH 64



void OLED_WrDat(uint8 data)
{
	byte i = 8;
	DC = 1;
	asm("nop");
	D0 = 0;
	asm("nop");
	while (i--)
	{
		if (data & 0x80)
		{
			D1 = 1;
		}
		else
		{
			D1 = 0;
		}
		D0 = 1;
		asm("nop");
		D0 = 0;
		data <<= 1;
	}
}
void OLED_WrCmd(byte cmd)
{
	byte i = 8;
	DC = 0;
	D0 = 0;
	while (i--)
	{
		if (cmd & 0x80)
		{
			D1 = 1;
		}
		else
		{
			D1 = 0;
		}
		D0 = 1;
		asm("nop");
		D0 = 0;
		cmd <<= 1;
	}
}
void OLED_Set_Pos(byte x, byte y)
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x & 0xf0) >> 4) | 0x10);
	OLED_WrCmd(x & 0x0f);//|0x01);
}
void OLED_Fill(byte bmp_data)
{
	byte y, x;

	for (y = 0; y<8; y++)
	{
		OLED_WrCmd(0xb0 + y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for (x = 0; x<X_WIDTH; x++)
			OLED_WrDat(bmp_data);
	}
}
void OLED_CLS(void)
{
	byte y, x;
	for (y = 0; y<8; y++)
	{
		OLED_WrCmd(0xb0 + y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for (x = 0; x<X_WIDTH; x++)
			OLED_WrDat(0);
	}
}
void OLED_DLY_ms(word ms)
{
	word a;
	while (ms)
	{
		a = 13350;
		while (a--);
		ms--;
	}
	return;
}

void OLED_Init(void)
{
	gpio_init(PTC10, GPO, 0);
	gpio_init(PTC12, GPO, 0);
	gpio_init(PTC14, GPO, 1);
	gpio_init(PTC16, GPO, 0);
	RESET = 0;
	OLED_DLY_ms(50);
	RESET = 1;
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(0xcf); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00);  //初始清屏
	OLED_Set_Pos(0, 0);

}
//==============================================================
//函数名： void OLED_PutPixel(byte x,byte y)
//功能描述：绘制一个点（x,y）
//参数：真实坐标值(x,y),x的范围0～127，y的范围0～64
//返回：无
//==============================================================
void OLED_PutPixel(byte x, byte y)
{
	byte data1;  //data1当前点的数据 

	OLED_Set_Pos(x, y);
	data1 = 0x01 << (y % 8);
	OLED_WrCmd(0xb0 + (y >> 3));
	OLED_WrCmd(((x & 0xf0) >> 4) | 0x10);
	OLED_WrCmd((x & 0x0f) | 0x00);
	OLED_WrDat(data1);
}
//==============================================================
//函数名： void OLED_Rectangle(byte x1,byte y1,
//                   byte x2,byte y2,byte color,byte gif)
//功能描述：绘制一个实心矩形
//参数：左上角坐标（x1,y1）,右下角坐标（x2，y2）
//      其中x1、x2的范围0～127，y1，y2的范围0～63，即真实坐标值
//返回：无
//==============================================================
void OLED_Rectangle(byte x1, byte y1, byte x2, byte y2, byte gif)
{
	byte n;

	OLED_Set_Pos(x1, y1 >> 3);
	for (n = x1; n <= x2; n++)
	{
		OLED_WrDat(0x01 << (y1 % 8));
		if (gif == 1) 	OLED_DLY_ms(50);
	}
	OLED_Set_Pos(x1, y2 >> 3);
	for (n = x1; n <= x2; n++)
	{
		OLED_WrDat(0x01 << (y2 % 8));
		if (gif == 1) 	OLED_DLY_ms(50);
	}

}

//==============================================================
//函数名：OLED_P8x16Str(byte x,byte y,byte *p)
//功能描述：写入一组标准ASCII字符串
//参数：显示的位置（x,y），y为页范围0～7，要显示的字符串
//返回：无
//==============================================================  
void OLED_P8x16Str(byte x, byte y, byte ch[])
{
	byte c = 0, i = 0, j = 0;

	while (ch[j] != '\0')
	{
		c = ch[j] - 32;
		if (x>120) { x = 0; y++; }
		OLED_Set_Pos(x, y);
		for (i = 0; i<8; i++)
		{
			OLED_WrDat(F8X16[c * 16 + i]);

		}
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i<8; i++)
		{
			OLED_WrDat(F8X16[c * 16 + i + 8]);

		}
		x += 8;
		j++;
	}
}
//输出汉字字符串
void OLED_P14x16Str(byte x, byte y, byte ch[])
{
	byte wm = 0, ii = 0;
	word adder = 1;

	while (ch[ii] != '\0')
	{
		wm = 0;
		adder = 1;
		while (F14x16_Idx[wm] > 127)
		{
			if (F14x16_Idx[wm] == ch[ii])
			{
				if (F14x16_Idx[wm + 1] == ch[ii + 1])
				{
					adder = wm * 14;
					break;
				}
			}
			wm += 2;
		}
		if (x>118) { x = 0; y++; }
		OLED_Set_Pos(x, y);
		if (adder != 1)// 显示汉字					
		{
			OLED_Set_Pos(x, y);
			for (wm = 0; wm < 14; wm++)
			{
				OLED_WrDat(F14x16[adder]);
				adder += 1;
			}
			OLED_Set_Pos(x, y + 1);
			for (wm = 0; wm < 14; wm++)
			{
				OLED_WrDat(F14x16[adder]);
				adder += 1;
			}
		}
		else			  //显示空白字符			
		{
			ii += 1;
			OLED_Set_Pos(x, y);
			for (wm = 0; wm < 16; wm++)
			{
				OLED_WrDat(0);
			}
			OLED_Set_Pos(x, y + 1);
			for (wm = 0; wm < 16; wm++)
			{
				OLED_WrDat(0);
			}
		}
		x += 14;
		ii += 2;
	}
}

/*============================================
函数名：OLED_Print(byte x, byte y, byte ch[])
作用:混合输出中英文
==========================================*/
/*============================================
布局:
汉字采用14号宋体字，y轴占两个单位
建议y轴布局为0,2,4,6
建议x轴汉字个数小于10个
否则可能会出现乱码问题
==========================================*/


void OLED_Print(byte x, byte y, byte ch[])
{
	byte ch2[3];
	byte ii = 0;
	while (ch[ii] != '\0')
	{
		if (ch[ii] > 127)
		{
			ch2[0] = ch[ii];
			ch2[1] = ch[ii + 1];
			ch2[2] = '\0';			//汉字为两个字节
			OLED_P14x16Str(x, y, ch2);	//显示汉字
			x += 14;
			ii += 2;
		}
		else
		{
			ch2[0] = ch[ii];
			ch2[1] = '\0';			//字母占一个字节
			OLED_P8x16Str(x, y, ch2);	//大字体
										//OLED_P6x8Str(x , y , ch2);       //小字体
			x += 8;
			ii += 1;
		}
	}
}

/*==========================================
函数名： void Draw_BMP(byte x,byte y)
功能描述：显示BMP图片128×64
==========================================*/
void Draw_BMP(byte x0, byte y0, byte x1, byte y1, uint8 bmp[])
{
	word ii = 0;
	byte x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y <= y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for (x = x0; x <= x1; x++)
		{
			OLED_WrDat(bmp[ii++]);
		}
	}
}
/*==========================================
函数名:void Display(int16 i,uint8 x,uint8 y)
作用:显示动态数字
==========================================*/
void Display(int16 i, uint8 x, uint8 y)
{
	int8 a[6] = { 0 };
	if (i<0)
	{
		a[0] = '-';
		i = -i;
	}
	else
		a[0] = '+';
	a[1] = i / 10000;
	a[2] = i % 10000 / 1000;
	a[3] = i % 1000 / 100;
	a[4] = i % 100 / 10;
	a[5] = i % 10;
	for (uint8 j = 0; j<6; j++)
	{
		switch (a[j])
		{
		case 0: {OLED_Print(x, y, "0"); }break;
		case 1: {OLED_Print(x, y, "1"); }break;
		case 2: {OLED_Print(x, y, "2"); }break;
		case 3: {OLED_Print(x, y, "3"); }break;
		case 4: {OLED_Print(x, y, "4"); }break;
		case 5: {OLED_Print(x, y, "5"); }break;
		case 6: {OLED_Print(x, y, "6"); }break;
		case 7: {OLED_Print(x, y, "7"); }break;
		case 8: {OLED_Print(x, y, "8"); }break;
		case 9: {OLED_Print(x, y, "9"); }break;
		case '-': {OLED_Print(x, y, "-"); }break;
		case '+': {OLED_Print(x, y, "+"); }break;
		default:break;
		}
		x += 10;
		if (x == 80)
			x = 20;
	}
}

/*==========================================
函数名:
void DisplayFloat(int16 i,uint8 x,uint8 y)
作用:显示动态数字
==========================================*/
void DisplayFloat(int16 i, uint8 x, uint8 y)
{
	int8 a[6] = { 0 };
	if (i<0)
	{
		a[0] = '-';
		i = -i;
	}
	else
		a[0] = '+';
	a[1] = i / 10000;
	a[2] = i % 10000 / 1000;
	a[3] = '.';
	a[4] = i % 1000 / 100;
	a[5] = i % 100 / 10;
	for (uint8 j = 0; j<6; j++)
	{
		switch (a[j])
		{
		case 0: {OLED_Print(x, y, "0"); }break;
		case 1: {OLED_Print(x, y, "1"); }break;
		case 2: {OLED_Print(x, y, "2"); }break;
		case 3: {OLED_Print(x, y, "3"); }break;
		case 4: {OLED_Print(x, y, "4"); }break;
		case 5: {OLED_Print(x, y, "5"); }break;
		case 6: {OLED_Print(x, y, "6"); }break;
		case 7: {OLED_Print(x, y, "7"); }break;
		case 8: {OLED_Print(x, y, "8"); }break;
		case 9: {OLED_Print(x, y, "9"); }break;
		case '-': {OLED_Print(x, y, "-"); }break;
		case '+': {OLED_Print(x, y, "+"); }break;
		case '.': {OLED_Print(x, y, "."); }break;
		default:break;
		}
		x += 10;
		if (x == 90)
			x = 20;
	}
}

