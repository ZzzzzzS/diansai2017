#include "include.h"
#include "PositionControl.h"
#include "data.h"

void AimPositionInit()
{
  AimPosition[Line1Left].H=41*2;
  AimPosition[Line1Left].W=29*2;
  
  AimPosition[Line1Middle].H=41*2;
  AimPosition[Line1Middle].W=44*2;
  
  AimPosition[Line1Right].H=40*2;
  AimPosition[Line1Right].W=59*2;
  
  AimPosition[Line2Left].H=25*2;
  AimPosition[Line2Left].W=29*2;
  
  AimPosition[Line2Middle].H=26*2;
  AimPosition[Line2Middle].W=45*2;
  
  AimPosition[Line2Right].H=25*2;
  AimPosition[Line2Right].W=59*2;
  
  AimPosition[Line3Left].H=10*2;
  AimPosition[Line3Left].W=29*2;
  
  AimPosition[Line3Middle].H=10*2;
  AimPosition[Line3Middle].W=45*2;
  
  AimPosition[Line3Right].H=10*2;
  AimPosition[Line3Right].W=57*2;
  
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
  ServoBase[W].PidBase.AimPosition=45*2;
  ServoBase[H].PidBase.AimPosition=26*2;
  
  ServoBase[W].PidBase.NowPosition=MainBall.CurrentBallPosition.W;
  ServoBase[H].PidBase.NowPosition=MainBall.CurrentBallPosition.H;
  
  ServoBase[W].PidBase.ErrorPosition[Now_Error]=ServoBase[W].PidBase.AimPosition-ServoBase[W].PidBase.NowPosition;
  ServoBase[H].PidBase.ErrorPosition[Now_Error]=ServoBase[H].PidBase.AimPosition-ServoBase[H].PidBase.NowPosition;
  
  ServoBase[W].PidBase.P=ServoBase[W].PidBase.PSet;
  ServoBase[W].PidBase.I=ServoBase[W].PidBase.ISet;
  ServoBase[W].PidBase.D=ServoBase[W].PidBase.DSet;
  ServoBase[H].PidBase.P=ServoBase[H].PidBase.PSet;
  ServoBase[H].PidBase.I=ServoBase[H].PidBase.ISet;
  ServoBase[H].PidBase.D=ServoBase[H].PidBase.DSet;
  
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
  CurrentAimPosition=AimPosition[Line2Middle];
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