#ifndef TOUCH_H
#define TOUCH_H

#define TouchY1 PTB0
#define TouchY2 PTB1
#define TouchX1 PTB2
#define TouchX2 PTB3
#define GetY    ADC0_SE8 
#define GetY2   ADC0_SE9
#define GetX    ADC0_SE12
#define GetX2   ADC0_SE13


#define MAXY 78
#define MAXX 195
#define MINX 35
#define MINY 25

typedef struct
{
  unsigned char x;
  unsigned char y;
}Position;

extern Position GetCurrentPosition();
extern Position GetRealPosition();

#endif //TOUCH_H