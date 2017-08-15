#include "include.h"
#include "control.h"
#include "data.h"


void PIDInit()
{
  ServoBase[W].PidBase.AimPosition=PathBase.AimPosition[Line2Middle].W;
  ServoBase[H].PidBase.AimPosition=PathBase.AimPosition[Line2Middle].H;
  
  ServoBase[W].PidBase.NowPosition=ServoBase[W].PidBase.AimPosition;
  ServoBase[H].PidBase.NowPosition=ServoBase[H].PidBase.AimPosition;
  
  ServoBase[W].PidBase.PSet=3;
  ServoBase[W].PidBase.ISet=0.05;
  ServoBase[W].PidBase.DSet=130;
  
  ServoBase[H].PidBase.PSet=3;
  ServoBase[H].PidBase.ISet=0.05;
  ServoBase[H].PidBase.DSet=130;
}
void ControlInit()
{
  ServoBase[W].Middle=750;
  ServoBase[H].Middle=680;
  ftm_pwm_init(Servo_FTM,Servo_W_FTM,Serv0_HZ,ServoBase[W].Middle);//舵机初始化，这个0待定
  ftm_pwm_init(Servo_FTM,Servo_H_FTM,Serv0_HZ,ServoBase[H].Middle);
}


void PIDControl(servo* Base)
{
  unsigned char IFlag=1;
  Base->PidBase.ErrorPosition[Now_Error]=Base->PidBase.AimPosition-Base->PidBase.NowPosition;
  
  if(Base->PidBase.ErrorPosition[Now_Error]>20)
    IFlag=0;
  else
    IFlag=1;
  
  Base->PidBase.IncrementPosition=(int)(Base->PidBase.P)*(Base->PidBase.ErrorPosition[Now_Error]);
  Base->PidBase.IncrementPosition+=IFlag*(Base->PidBase.I)*(Base->PidBase.ErrorPosition[Now_Error]+Base->PidBase.ErrorPosition[last_Error]);
  Base->PidBase.IncrementPosition+=(Base->PidBase.D)*(Base->PidBase.ErrorPosition[Now_Error]-2*Base->PidBase.ErrorPosition[last_Error]+Base->PidBase.ErrorPosition[lastest_Error]);
  
  Base->PidBase.ErrorPosition[lastest_Error]=Base->PidBase.ErrorPosition[last_Error];
  Base->PidBase.ErrorPosition[last_Error]=Base->PidBase.ErrorPosition[Now_Error];
  
  Base->PidBase.PIDOutPosition+=Base->PidBase.IncrementPosition;
  
}

void PIDControlPositional(servo *Base)
{
  if((Base->PidBase.ErrorPosition[Now_Error]<10&&Base->PidBase.ErrorPosition[Now_Error]>1)||(Base->PidBase.ErrorPosition[Now_Error]>-10&&Base->PidBase.ErrorPosition[Now_Error]<-1))
    Base->PidBase.IntergatePosition+=Base->PidBase.ErrorPosition[Now_Error];
  //else
    //Base->PidBase.IntergatePosition=0;
  
  Base->PidBase.DeltaError=Base->PidBase.ErrorPosition[Now_Error]-Base->PidBase.ErrorPosition[last_Error];
  Base->PidBase.ErrorPosition[last_Error]=Base->PidBase.ErrorPosition[Now_Error];
  
  Base->PidBase.PIDOutPosition=(int)Base->PidBase.P*Base->PidBase.ErrorPosition[Now_Error];
  Base->PidBase.PIDOutPosition+=(int)Base->PidBase.D*Base->PidBase.DeltaError;
  
  Base->PidBase.PIDOutPosition+=Base->PidBase.IntergatePosition*Base->PidBase.I;
    
  
  Base->OutPosition=Base->PidBase.PIDOutPosition;
}

void ControlOut()
{
<<<<<<< HEAD
<<<<<<< HEAD
  int OutW=MIDDLE_W-ServoBase[W].PidBase.PIDOutPosition;
  int OutH=MIDDLE_H+ServoBase[H].PidBase.PIDOutPosition;
=======
  int OutW=MIDDLE_W-ServoBase[W].OutPosition;
  int OutH=MIDDLE_H+ServoBase[H].OutPosition;
>>>>>>> master
=======
  int OutW=ServoBase[W].Middle-ServoBase[W].OutPosition;
  int OutH=ServoBase[H].Middle+ServoBase[H].OutPosition;
>>>>>>> master
  
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
  //printf("%d %d\n",OutW,OutH);
  
}
