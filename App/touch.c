#include "include.h"
#include "touch.h"

typedef unsigned char uchar;

uchar GetXPosition();
uchar GetYPosition();


uchar GetXPosition()
{
  gpio_init(TouchY1,GPO,1);
  gpio_init(TouchY2,GPO,0);
  port_init_NoALT(TouchY1,PULLUP);
  port_init_NoALT(TouchY2,PULLDOWN);
  adc_init(GetX);
  adc_init(GetX2);
  int X;
  int X2;
  X2=255-adc_once(GetX2,ADC_8bit);
  X=(adc_once(GetX,ADC_8bit));
  //X=(X+X2)/2;
  if(X<5)
    return 0;
  else
    return X;
  
}

uchar GetYPosition()
{
  gpio_init(TouchX1,GPO,1);
  gpio_init(TouchX2,GPO,0);
  port_init_NoALT(TouchX1,PULLUP);
  port_init_NoALT(TouchX2,PULLDOWN);
  adc_init(GetY);
  adc_init(GetY2);
  int Y;
  int Y2;
  //Y2=(255-adc_once(GetY2,ADC_8bit);
  Y=(adc_once(GetY,ADC_8bit));
  ////Y=(Y+Y2)/2;
  if(Y<5)
    return 0;
  else
    return Y;
}

Position GetCurrentPosition()
{
  Position CurrentPosition={0};
  CurrentPosition.x=GetXPosition();
  //DELAY_MS(1);
  CurrentPosition.y=GetYPosition();
  
  return CurrentPosition;
}

Position GetRealPosition()
{
  Position Base=GetCurrentPosition();
  
  Base.x=100*(Base.x-MINX)/(MAXX-MINX);
  Base.y=100*(Base.y-MINY)/(MAXY-MINY);
  return Base;
}