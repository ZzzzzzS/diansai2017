#ifndef TOUCH_H
#define TOUCH_H

#define TouchY1 PTE3
#define TouchY2 PTE5
#define TouchX1 PTE2
#define TouchX2 PTE6
#define GetY    ADC1_SE7a 
//#define GetY2   ADC0_SE9
#define GetX    ADC1_SE6a
//#define GetX2   ADC0_SE13


#define MAXY 78
#define MAXX 195
#define MINX 35
#define MINY 25

typedef struct
{
  unsigned char x;
  unsigned char y;
}touchposition;

extern touchposition GetCurrentPosition();
extern touchposition GetRealPosition();

#endif //TOUCH_H