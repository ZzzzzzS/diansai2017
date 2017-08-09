#include "include.h"
#include "PositionControl.h"
#include "data.h"

void AimPositionInit()
{
  AimPosition[Line1Left].H=0;
  AimPosition[Line1Left].W=0;
  
  AimPosition[Line1Middle].H=0;
  AimPosition[Line1Middle].W=0;
  
  AimPosition[Line1Right].H=0;
  AimPosition[Line1Right].W=0;
  
  AimPosition[Line2Left].H=0;
  AimPosition[Line2Left].W=0;
  
  AimPosition[Line2Middle].H=0;
  AimPosition[Line2Middle].W=0;
  
  AimPosition[Line2Right].H=0;
  AimPosition[Line2Right].W=0;
  
  AimPosition[Line3Left].H=0;
  AimPosition[Line3Left].W=0;
  
  AimPosition[Line3Middle].H=0;
  AimPosition[Line3Middle].W=0;
  
  AimPosition[Line3Right].H=0;
  AimPosition[Line3Right].W=0;
  
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
  //将当前位置转化成误差位置
  //分段调节PID参数
  ServoBase[W].PidBase.AimPosition=CurrentAimPosition.W;
  ServoBase[H].PidBase.AimPosition=CurrentAimPosition.H;
  
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