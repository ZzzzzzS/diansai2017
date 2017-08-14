#include "include.h"
#include "PositionControl.h"
#include "data.h"

void AimPositionInit()
{
  AimPosition[Line1Left].H=89;
  AimPosition[Line1Left].W=40;
  
  AimPosition[Line1Middle].H=90;
  AimPosition[Line1Middle].W=76;
  
  AimPosition[Line1Right].H=90;
  AimPosition[Line1Right].W=112;
  
  AimPosition[Line2Left].H=53;
  AimPosition[Line2Left].W=39;
  
  AimPosition[Line2Middle].H=53;
  AimPosition[Line2Middle].W=75;
  
  AimPosition[Line2Right].H=53;
  AimPosition[Line2Right].W=112;
  
  AimPosition[Line3Left].H=17;
  AimPosition[Line3Left].W=40;
  
  AimPosition[Line3Middle].H=18;
  AimPosition[Line3Middle].W=75;
  
  AimPosition[Line3Right].H=19;
  AimPosition[Line3Right].W=112;
  
}

void PathInit()
{
  path[0]=AimPosition[Line2Middle];
  path[1]=AimPosition[Line1Right];
  path[2]=AimPosition[Line1Left];
  path[3].H=0;
  path[3].W=0;
}

void CalculatePosition()
{
  ServoBase[W].PidBase.AimPosition=CurrentAimPosition.W;
  ServoBase[H].PidBase.AimPosition=CurrentAimPosition.H;
  
  ServoBase[W].PidBase.NowPosition=MainBall.CurrentBallPosition.W;
  ServoBase[H].PidBase.NowPosition=MainBall.CurrentBallPosition.H;
  
  ServoBase[W].PidBase.ErrorPosition[Now_Error]=ServoBase[W].PidBase.AimPosition-ServoBase[W].PidBase.NowPosition;
  ServoBase[H].PidBase.ErrorPosition[Now_Error]=ServoBase[H].PidBase.AimPosition-ServoBase[H].PidBase.NowPosition;
  
  ServoBase[W].PidBase.DeltaError=ServoBase[W].PidBase.ErrorPosition[Now_Error]-ServoBase[W].PidBase.ErrorPosition[last_Error];
  ServoBase[H].PidBase.DeltaError=ServoBase[H].PidBase.ErrorPosition[Now_Error]-ServoBase[H].PidBase.ErrorPosition[last_Error];
  
  ServoBase[W].PidBase.P=ServoBase[W].PidBase.PSet;
  ServoBase[W].PidBase.I=ServoBase[W].PidBase.ISet;
  ServoBase[W].PidBase.D=ServoBase[W].PidBase.DSet;
  ServoBase[H].PidBase.P=ServoBase[H].PidBase.PSet;
  ServoBase[H].PidBase.I=ServoBase[H].PidBase.ISet;
  ServoBase[H].PidBase.D=ServoBase[H].PidBase.DSet;
  
  if(ServoBase[W].PidBase.ErrorPosition[Now_Error]<7&&ServoBase[W].PidBase.ErrorPosition[Now_Error]>-7)
  {       
      ServoBase[W].PidBase.D=30;
      ServoBase[W].PidBase.P=1;
  }
  if(ServoBase[H].PidBase.ErrorPosition[Now_Error]<7&&ServoBase[H].PidBase.ErrorPosition[Now_Error]>-7)
  {       
      ServoBase[H].PidBase.D=30;
      ServoBase[H].PidBase.P=1;
  }

  SetPID(&ServoBase[W]);
  SetPID(&ServoBase[H]);
  
  
}

void SetPID(servo* Base)
{
  /*if(Base->PidBase.ErrorPosition[Now_Error]>0)
  {
    
  }
  if(Base->PidBase.ErrorPosition[Now_Error]<7&&Base->PidBase.ErrorPosition[Now_Error]>-7)
  {
    Base->PidBase.D=Base->PidBase.DSet*(8-Base->PidBase.ErrorPosition[Now_Error]);
  }*/
  
}

bool AtPosition(position base)
{
  static unsigned char counter=0;
  
  
  if((ServoBase[W].PidBase.ErrorPosition[Now_Error]<4&&ServoBase[W].PidBase.ErrorPosition[Now_Error]>-4) && (ServoBase[H].PidBase.ErrorPosition[Now_Error]<4&&ServoBase[H].PidBase.ErrorPosition[Now_Error]>-4))
  {
    counter++;
  }
  else
  {
    counter=0;
  }
  
  if(counter>StableTimes)
  {
    gpio_set(PTA8,1);
    return true;
  }
    gpio_set(PTA8,0);
  return false;
}

void SetAimPosition()
{
  
  static char PassPoint=0;
  
  if(AtPosition(path[CurrentPath]))
  {
    if(path[CurrentPath+1].H==0&&path[CurrentPath+1].W==0)//没有下一个点就停止规划新的路径
    {
      CurrentPath=0;
      CurrentAimPosition=path[CurrentPath];
      return;
    }
    else
    {
    CurrentPath++;
    CurrentAimPosition=path[CurrentPath];
    }
  }
}