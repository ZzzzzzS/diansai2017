#include "include.h"
#include "PositionControl.h"
#include "data.h"

void AimPositionInit()
{
  AimPosition[Line1Left].H=48;
  AimPosition[Line1Left].W=28;
  
  AimPosition[Line1Middle].H=48;
  AimPosition[Line1Middle].W=45;
  
  AimPosition[Line1Right].H=48;
  AimPosition[Line1Right].W=61;
  
  AimPosition[Line2Left].H=32;
  AimPosition[Line2Left].W=27;
  
  AimPosition[Line2Middle].H=32;
  AimPosition[Line2Middle].W=46;
  
  AimPosition[Line2Right].H=32;
  AimPosition[Line2Right].W=63;
  
  AimPosition[Line3Left].H=14;
  AimPosition[Line3Left].W=28;
  
  AimPosition[Line3Middle].H=14;
  AimPosition[Line3Middle].W=46;
  
  AimPosition[Line3Right].H=15;
  AimPosition[Line3Right].W=62;
  
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
  ServoBase[W].PidBase.AimPosition=23;
  ServoBase[H].PidBase.AimPosition=22;
  
  ServoBase[W].PidBase.NowPosition=MainBall.CurrentBallPosition.W;
  ServoBase[H].PidBase.NowPosition=MainBall.CurrentBallPosition.H;
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