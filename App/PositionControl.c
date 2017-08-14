#include "include.h"
#include "PositionControl.h"
#include "data.h"

void AimPositionInit()
{
  AimPosition[Line1Left].H=88;
  AimPosition[Line1Left].W=40;
  
  AimPosition[Line1Middle].H=90;
  AimPosition[Line1Middle].W=75;
  
  AimPosition[Line1Right].H=90;
  AimPosition[Line1Right].W=112;
  
  AimPosition[Line2Left].H=52;
  AimPosition[Line2Left].W=40;
  
  AimPosition[Line2Middle].H=52;
  AimPosition[Line2Middle].W=75;
  
  AimPosition[Line2Right].H=52;
  AimPosition[Line2Right].W=112;
  
  AimPosition[Line3Left].H=16;
  AimPosition[Line3Left].W=39;
  
  AimPosition[Line3Middle].H=16;
  AimPosition[Line3Middle].W=75;
  
  AimPosition[Line3Right].H=17;
  AimPosition[Line3Right].W=113;
  
}

void PathInit()
{
  path[0]=AimPosition[Line2Middle];
  path[1]=AimPosition[Line3Right];
  path[2].H=0;
  path[2].W=0;
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
  
  /*if(ServoBase[W].PidBase.ErrorPosition[Now_Error]<5&&ServoBase[W].PidBase.ErrorPosition[Now_Error]>-5)
  {
    ServoBase[W].PidBase.D=ServoBase[W].PidBase.PSet/2;
  }
    
  
  if(ServoBase[H].PidBase.ErrorPosition[Now_Error]<5&&ServoBase[H].PidBase.ErrorPosition[Now_Error]>-5)
  {
    ServoBase[H].PidBase.D=ServoBase[H].PidBase.PSet/2;
  }
  
  if(ServoBase[W].PidBase.ErrorPosition[Now_Error]>0)
    ServoBase[W].PidBase.P=ServoBase[W].PidBase.PSet*ServoBase[W].PidBase.ErrorPosition[Now_Error]*0.02;
  else
    ServoBase[W].PidBase.P=-ServoBase[W].PidBase.PSet*ServoBase[W].PidBase.ErrorPosition[Now_Error]*0.02;
  
  if(ServoBase[H].PidBase.ErrorPosition[Now_Error]>0)
    ServoBase[H].PidBase.P=ServoBase[H].PidBase.PSet*ServoBase[H].PidBase.ErrorPosition[Now_Error]*0.02;
  else
    ServoBase[H].PidBase.P=-ServoBase[H].PidBase.PSet*ServoBase[H].PidBase.ErrorPosition[Now_Error]*0.02;
  */
  
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
  static char counter=0;
  
  
  if((((base.H-MainBall.CurrentBallPosition.H)*(base.H-MainBall.CurrentBallPosition.H))+(base.W-MainBall.CurrentBallPosition.W)*(base.W-MainBall.CurrentBallPosition.W))<=(StableRange*StableRange))
  {
    counter++;
  }
  else
  {
    counter=0;
  }
  
  if(counter>StableTimes)
  {
    return true;
  }

  return false;
}

void SetAimPosition()
{
  //CurrentAimPosition=AimPosition[Line1Middle];
  return;
  
  static int flag=0;
  if(path[CurrentPath+1].H==0&&path[CurrentPath+1].W==0)//没有下一个点就停止规划新的路径
  {
    return;
  }
  
  if(flag!=0)
  {
    flag++;
    if(flag>=400)
    {
      CurrentPath++;
      flag=0;
    }
  }
  
  if(AtPosition(path[CurrentPath]))
  {
    flag=1;
  }
}