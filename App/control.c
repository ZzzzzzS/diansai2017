#include "include.h"
#include "control.h"
#include "data.h"


void PIDInit()
{
  ServoBase[W].PidBase.AimPosition=AimPosition[Line2Middle].W;
  ServoBase[H].PidBase.AimPosition=AimPosition[Line2Middle].H;
  
  ServoBase[W].PidBase.NowPosition=ServoBase[W].PidBase.AimPosition;
  ServoBase[H].PidBase.NowPosition=ServoBase[H].PidBase.AimPosition;
  
  ServoBase[W].PidBase.P=0.05;
  ServoBase[W].PidBase.I=0;
  ServoBase[W].PidBase.D=0;
  
  ServoBase[W].PidBase.P=0.05;
  ServoBase[W].PidBase.I=0;
  ServoBase[W].PidBase.D=0;
}
void ControlInit()
{
  ftm_pwm_init(Servo_FTM,Servo_W_FTM,Serv0_HZ,500);//舵机初始化，这个0待定
  ftm_pwm_init(Servo_FTM,Servo_H_FTM,Serv0_HZ,500);
}


void PIDControl(servo* Base)
{
  unsigned char IFlag=1;
  Base->PidBase.ErrorPosition[Now_Error]=Base->PidBase.AimPosition-Base->PidBase.NowPosition;
  
  if(Base->PidBase.ErrorPosition[Now_Error]>20)
    IFlag=0;
  else
    IFlag=1;
  
  Base->PidBase.IncrementPosition=(Base->PidBase.P)*(Base->PidBase.ErrorPosition[Now_Error]);
  Base->PidBase.IncrementPosition+=IFlag*(Base->PidBase.I)*(Base->PidBase.ErrorPosition[Now_Error]+Base->PidBase.ErrorPosition[last_Error]);
  Base->PidBase.IncrementPosition+=(Base->PidBase.D)*(Base->PidBase.ErrorPosition[Now_Error]-2*Base->PidBase.ErrorPosition[last_Error]+Base->PidBase.ErrorPosition[lastest_Error]);
  
  Base->PidBase.ErrorPosition[lastest_Error]=Base->PidBase.ErrorPosition[last_Error];
  Base->PidBase.ErrorPosition[last_Error]=Base->PidBase.ErrorPosition[Now_Error];
  
  Base->PidBase.PIDOutPosition+=Base->PidBase.IncrementPosition;
  
}

void ControlOut()
{
  int OutW=MIDDLE_W+ServoBase[W].PidBase.PIDOutPosition;
  int OutH=MIDDLE_H+ServoBase[H].PidBase.PIDOutPosition;
  
  if(OutW>=MAX_POSITION_W)
    OutW=MAX_POSITION_W;
  else if(OutW<=MIN_POSITION_W)
    OutW=MIN_POSITION_W;
  
  if(OutH>=MAX_POSITION_H)
    OutH=MAX_POSITION_H;
  else if(OutH<=MIN_POSITION_H)
    OutH=MIN_POSITION_H;
  
  ftm_pwm_duty(Servo_FTM, Servo_W_FTM, OutW);
  ftm_pwm_duty(Servo_FTM, Servo_H_FTM, OutH);
  
}
