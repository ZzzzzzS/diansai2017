#include "include.h"
#include "PositionControl.h"
#include "data.h"
#include "math.h"

char GetType(position Aim,position Current)//利用坐标差判断位置类型，其实这样不太好，但是也不想修改了
{
  if(((Aim.H-Current.H<45)&&(Aim.H-Current.H>-45)) && ((Aim.W-Current.W<45)&&(Aim.W-Current.W>-45)))
    return BasicType;
  
  else if(((Aim.H-Current.H>65)||(Aim.H-Current.H<-65)) && ((Aim.W-Current.W>65)||(Aim.W-Current.W<-65)))
    return BiagonalType;
  
  else if(((Aim.H-Current.H<20)&&(Aim.H-Current.H>-20)) && (Aim.W-Current.W>65))
    return GapWType;
  
  else if(((Aim.H-Current.H<20)&&(Aim.H-Current.H>-20)) && (Aim.W-Current.W<-65))
    return GapWFType;
 
  else if(((Aim.W-Current.W<20)&&(Aim.W-Current.W>-20)) && (Aim.H-Current.H>65))
    return GapHType;
  
  else if(((Aim.W-Current.W<20)&&(Aim.W-Current.W>-20)) && (Aim.H-Current.H<-65))
    return GapHFType;
  else 
    return BasicType;
}

void AimPositionInit()
{
  /*PathBase.AimPosition[Line3Left].H=89;
  PathBase.AimPosition[Line3Left].W=40;
  PathBase.AimPosition[Line3Left].PositionNumber=Line3Left;
  
  PathBase.AimPosition[Line3Middle].H=90;
  PathBase.AimPosition[Line3Middle].W=75;
  PathBase.AimPosition[Line3Middle].PositionNumber=Line3Middle;
  
  PathBase.AimPosition[Line3Right].H=90;
  PathBase.AimPosition[Line3Right].W=112;
  PathBase.AimPosition[Line3Right].PositionNumber=Line3Right;
  
  PathBase.AimPosition[Line2Left].H=53;
  PathBase.AimPosition[Line2Left].W=39;
  PathBase.AimPosition[Line2Left].PositionNumber=Line2Left;
  
  PathBase.AimPosition[Line2Middle].H=53;
  PathBase.AimPosition[Line2Middle].W=75;
  PathBase.AimPosition[Line2Middle].PositionNumber=Line2Middle;
  
  PathBase.AimPosition[Line2Right].H=53;
  PathBase.AimPosition[Line2Right].W=113;
  PathBase.AimPosition[Line2Right].PositionNumber=Line2Right;
  
  PathBase.AimPosition[Line1Left].H=16;
  PathBase.AimPosition[Line1Left].W=39;
  PathBase.AimPosition[Line1Left].PositionNumber=Line1Left;
  
  PathBase.AimPosition[Line1Middle].H=16;
  PathBase.AimPosition[Line1Middle].W=75;
  PathBase.AimPosition[Line1Middle].PositionNumber=Line1Middle;
  
  PathBase.AimPosition[Line1Right].H=17;
  PathBase.AimPosition[Line1Right].W=112;
  PathBase.AimPosition[Line1Right].PositionNumber=Line1Right;

  PathBase.AimPosition[TransPoint3L].H=70;
  PathBase.AimPosition[TransPoint3L].W=56;
  PathBase.AimPosition[TransPoint3L].PositionNumber=TransPoint3L;
  
  PathBase.AimPosition[TransPoint3R].H=65;
  PathBase.AimPosition[TransPoint3R].W=90;
  PathBase.AimPosition[TransPoint3R].PositionNumber=TransPoint3R;
    
  PathBase.AimPosition[TransPoint1L].H=41;
  PathBase.AimPosition[TransPoint1L].W=59;
  PathBase.AimPosition[TransPoint1L].PositionNumber=TransPoint1L;
    
  PathBase.AimPosition[TransPoint1R].H=42;
  PathBase.AimPosition[TransPoint1R].W=91;
  PathBase.AimPosition[TransPoint1R].PositionNumber=TransPoint1R;
  
  PathBase.AimPosition[TransPoint2R].H=54;
  PathBase.AimPosition[TransPoint2R].W=99;
  PathBase.AimPosition[TransPoint2R].PositionNumber=TransPoint2R;
  
  PathBase.AimPosition[TransPoint2L].H=54;
  PathBase.AimPosition[TransPoint2L].W=51;
  PathBase.AimPosition[TransPoint2L].PositionNumber=TransPoint2L;
  
  PathBase.AimPosition[TransPoint1M].H=28;
  PathBase.AimPosition[TransPoint1M].W=75;
  PathBase.AimPosition[TransPoint1M].PositionNumber=TransPoint1M;
  
  PathBase.AimPosition[TransPoint3M].H=75;
  PathBase.AimPosition[TransPoint3M].W=75;
  PathBase.AimPosition[TransPoint3M].PositionNumber=TransPoint3M;*/
  
  PathBase.AimPosition[Line3Left].H=91;//初始化9+8个点
  PathBase.AimPosition[Line3Left].W=112;
  PathBase.AimPosition[Line3Left].PositionNumber=Line3Left;
  
  PathBase.AimPosition[Line3Middle].H=54;
  PathBase.AimPosition[Line3Middle].W=113;
  PathBase.AimPosition[Line3Middle].PositionNumber=Line3Middle;
  
  PathBase.AimPosition[Line3Right].H=18;
  PathBase.AimPosition[Line3Right].W=112;
  PathBase.AimPosition[Line3Right].PositionNumber=Line3Right;
  
  PathBase.AimPosition[Line2Left].H=90;
  PathBase.AimPosition[Line2Left].W=76;
  PathBase.AimPosition[Line2Left].PositionNumber=Line2Left;
  
  PathBase.AimPosition[Line2Middle].H=53;
  PathBase.AimPosition[Line2Middle].W=76;
  PathBase.AimPosition[Line2Middle].PositionNumber=Line2Middle;
  
  PathBase.AimPosition[Line2Right].H=18;
  PathBase.AimPosition[Line2Right].W=76;
  PathBase.AimPosition[Line2Right].PositionNumber=Line2Right;
  
  PathBase.AimPosition[Line1Left].H=89;
  PathBase.AimPosition[Line1Left].W=40;
  PathBase.AimPosition[Line1Left].PositionNumber=Line1Left;
  
  PathBase.AimPosition[Line1Middle].H=53;
  PathBase.AimPosition[Line1Middle].W=40;
  PathBase.AimPosition[Line1Middle].PositionNumber=Line1Middle;
  
  PathBase.AimPosition[Line1Right].H=17;
  PathBase.AimPosition[Line1Right].W=41;
  PathBase.AimPosition[Line1Right].PositionNumber=Line1Right;

  PathBase.AimPosition[TransPoint3L].H=72;
  PathBase.AimPosition[TransPoint3L].W=93;
  PathBase.AimPosition[TransPoint3L].PositionNumber=TransPoint3L;
  
  PathBase.AimPosition[TransPoint3R].H=39;
  PathBase.AimPosition[TransPoint3R].W=94;
  PathBase.AimPosition[TransPoint3R].PositionNumber=TransPoint3R;
    
  PathBase.AimPosition[TransPoint1L].H=70;
  PathBase.AimPosition[TransPoint1L].W=60;
  PathBase.AimPosition[TransPoint1L].PositionNumber=TransPoint1L;
    
  PathBase.AimPosition[TransPoint1R].H=38;//x0+10*sin(pi/8)
  PathBase.AimPosition[TransPoint1R].W=60;
  PathBase.AimPosition[TransPoint1R].PositionNumber=TransPoint1R;
  
  PathBase.AimPosition[TransPoint2R].H=32;
  PathBase.AimPosition[TransPoint2R].W=76;
  PathBase.AimPosition[TransPoint2R].PositionNumber=TransPoint2R;
  
  PathBase.AimPosition[TransPoint2L].H=77;
  PathBase.AimPosition[TransPoint2L].W=75;
  PathBase.AimPosition[TransPoint2L].PositionNumber=TransPoint2L;
  
  PathBase.AimPosition[TransPoint1M].H=53;
  PathBase.AimPosition[TransPoint1M].W=54;
  PathBase.AimPosition[TransPoint1M].PositionNumber=TransPoint1M;
  
  PathBase.AimPosition[TransPoint3M].H=54;
  PathBase.AimPosition[TransPoint3M].W=100;
  PathBase.AimPosition[TransPoint3M].PositionNumber=TransPoint3M;
  
}

void PathInit()//初始化路径
{
  PathBase.StoredPath[BasicFunction1][0]=PathBase.AimPosition[Line1Middle];
  PathBase.StoredPath[BasicFunction1][1].H=0;
  PathBase.StoredPath[BasicFunction1][1].W=0;
  
  PathBase.StoredPath[BasicFunction2][0]=PathBase.AimPosition[Line1Left];
  PathBase.StoredPath[BasicFunction2][1]=PathBase.AimPosition[Line2Middle];
  PathBase.StoredPath[BasicFunction2][2].H=0;
  PathBase.StoredPath[BasicFunction2][2].W=0;
  
  PathBase.StoredPath[BasicFunction3][0]=PathBase.AimPosition[Line1Left];
  PathBase.StoredPath[BasicFunction3][1]=PathBase.AimPosition[Line2Left];
  PathBase.StoredPath[BasicFunction3][2]=PathBase.AimPosition[Line2Middle];
  PathBase.StoredPath[BasicFunction3][3].H=0;
  PathBase.StoredPath[BasicFunction3][3].W=0;
  
  PathBase.StoredPath[BasicFunction4][0]=PathBase.AimPosition[Line1Left];
  PathBase.StoredPath[BasicFunction4][1]=PathBase.AimPosition[Line3Right];
  PathBase.StoredPath[BasicFunction4][2].H=0;
  PathBase.StoredPath[BasicFunction4][2].W=0;
  
  PathBase.StoredPath[AdvanceFunction1][0]=PathBase.AimPosition[Line1Left];
  PathBase.StoredPath[AdvanceFunction1][1]=PathBase.AimPosition[Line1Middle];
  PathBase.StoredPath[AdvanceFunction1][2]=PathBase.AimPosition[Line2Right];
  PathBase.StoredPath[AdvanceFunction1][3]=PathBase.AimPosition[Line3Right];
  PathBase.StoredPath[AdvanceFunction1][4].H=0;
  PathBase.StoredPath[AdvanceFunction1][4].W=0;
  
  PathBase.StoredPath[AdvanceFunction3][0]=PathBase.AimPosition[Line2Left];
  PathBase.StoredPath[AdvanceFunction3][1]=PathBase.AimPosition[TransPoint1L];
  PathBase.StoredPath[AdvanceFunction3][2]=PathBase.AimPosition[TransPoint1M];
  PathBase.StoredPath[AdvanceFunction3][3]=PathBase.AimPosition[TransPoint1R];
  PathBase.StoredPath[AdvanceFunction3][4]=PathBase.AimPosition[TransPoint2R];
  PathBase.StoredPath[AdvanceFunction3][5]=PathBase.AimPosition[TransPoint3R];
  PathBase.StoredPath[AdvanceFunction3][6]=PathBase.AimPosition[TransPoint3M];
  PathBase.StoredPath[AdvanceFunction3][7]=PathBase.AimPosition[TransPoint3L];
  PathBase.StoredPath[AdvanceFunction3][8]=PathBase.AimPosition[TransPoint2L];
  PathBase.StoredPath[AdvanceFunction3][9]=PathBase.AimPosition[TransPoint1L];
  PathBase.StoredPath[AdvanceFunction3][10]=PathBase.AimPosition[TransPoint1M];
  PathBase.StoredPath[AdvanceFunction3][11]=PathBase.AimPosition[TransPoint1R];
  PathBase.StoredPath[AdvanceFunction3][12]=PathBase.AimPosition[TransPoint2R];
  PathBase.StoredPath[AdvanceFunction3][13]=PathBase.AimPosition[TransPoint3R];
  PathBase.StoredPath[AdvanceFunction3][14]=PathBase.AimPosition[TransPoint3M];
  PathBase.StoredPath[AdvanceFunction3][15]=PathBase.AimPosition[TransPoint3L];
  PathBase.StoredPath[AdvanceFunction3][16]=PathBase.AimPosition[TransPoint2L];
  PathBase.StoredPath[AdvanceFunction3][17]=PathBase.AimPosition[TransPoint1L];
  PathBase.StoredPath[AdvanceFunction3][18]=PathBase.AimPosition[TransPoint1M];
  PathBase.StoredPath[AdvanceFunction3][19]=PathBase.AimPosition[TransPoint1R];
  PathBase.StoredPath[AdvanceFunction3][20]=PathBase.AimPosition[TransPoint2R];
  PathBase.StoredPath[AdvanceFunction3][21]=PathBase.AimPosition[TransPoint3R];
  PathBase.StoredPath[AdvanceFunction3][22]=PathBase.AimPosition[TransPoint3M];
  PathBase.StoredPath[AdvanceFunction3][23]=PathBase.AimPosition[TransPoint3L];
  PathBase.StoredPath[AdvanceFunction3][24]=PathBase.AimPosition[TransPoint2L];
  PathBase.StoredPath[AdvanceFunction3][25]=PathBase.AimPosition[TransPoint1L];
  PathBase.StoredPath[AdvanceFunction3][26]=PathBase.AimPosition[TransPoint1M];
  PathBase.StoredPath[AdvanceFunction3][27]=PathBase.AimPosition[TransPoint1R];
  PathBase.StoredPath[AdvanceFunction3][28]=PathBase.AimPosition[Line3Right];
  PathBase.StoredPath[AdvanceFunction1][29].H=0;
  PathBase.StoredPath[AdvanceFunction1][29].W=0;
}

void CalculatePosition()
{
  ServoBase[W].PidBase.AimPosition=MainBall.CurrentAimPosition.W;
  ServoBase[H].PidBase.AimPosition=MainBall.CurrentAimPosition.H;
  
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

  SetPID(&ServoBase[W]);
  SetPID(&ServoBase[H]);
}

void SetPID(servo* Base)//可以在这个函数里加分段PID
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
  
  if((ServoBase[W].PidBase.ErrorPosition[Now_Error]<StableRange&&ServoBase[W].PidBase.ErrorPosition[Now_Error]>-StableRange) && (ServoBase[H].PidBase.ErrorPosition[Now_Error]<StableRange&&ServoBase[H].PidBase.ErrorPosition[Now_Error]>-StableRange))
  {
    counter++;
  }
  else
  {
    counter=0;
  }
  
  if(counter>StableTimes)
  {
    MainBall.AimTime.MS=0;
    MainBall.AimTime.S=0;
    gpio_set(PTA8,1);
    return true;
  }
    gpio_set(PTA8,0);
  return false;
}

bool AtPositionNonBlocking(position base)
{
  if((ServoBase[W].PidBase.ErrorPosition[Now_Error]<7&&ServoBase[W].PidBase.ErrorPosition[Now_Error]>-7) && (ServoBase[H].PidBase.ErrorPosition[Now_Error]<7&&ServoBase[H].PidBase.ErrorPosition[Now_Error]>-7))
  {
    //gpio_set(PTA8,1);
    return true;
  }
    gpio_set(PTA8,0);
    return false;
  
}

void SetAimPosition()//设定目标点
{
  if(PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter+1].H==0)//如果是最后一个点，就不再继续设点
  {
    AtPosition(MainBall.CurrentAimPosition);
    return;
  }
  
  TimeAddMS(MainBall.AllTime,50);
  TimeAddMS(MainBall.AimTime,50);
  
  if(PathBase.Function==AdvanceFunction3)//如果是发挥功能3就单独处理
  {
    if(PathBase.CurrentPositionCounter==0)
    {
      if(AtPosition(MainBall.CurrentAimPosition))
      {
      PathBase.TransPointFlag=false;
      PathBase.CurrentPositionCounter++;
      MainBall.CurrentAimPosition=PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter];
      }  
    }
    else
    {
      if(AtPositionNonBlocking(MainBall.CurrentAimPosition))
      {
        PathBase.TransPointFlag=false;
        PathBase.CurrentPositionCounter++;
        MainBall.CurrentAimPosition=PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter];
      }
    }
    return;
  }
  
  
  if(PathBase.TransPointFlag==true)//当前目标点是转移点的情况
  {
    if(AtPositionNonBlocking(MainBall.CurrentAimPosition))
    {
      PathBase.TransPointFlag=false;
      PathBase.CurrentPositionCounter++;
      MainBall.CurrentAimPosition=PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter];
      
    }
  }
  else if(PathBase.TransPointFlag==false)//当前点不是转移点的情况
  {
    if(AtPosition(MainBall.CurrentAimPosition))
    {
      char type=GetType(MainBall.CurrentAimPosition,PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter+1]);
      
      if(type==BasicType)//判断出来的不同的目标点类型设计不同的转移点，这一段写得不好。
      {
          PathBase.TransPointFlag=false;
          PathBase.CurrentPositionCounter++;
          MainBall.CurrentAimPosition=PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter];
      }
      
      else if(type==BiagonalType)
      {
          PathBase.TransPointFlag=true;
          if((MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line1Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line1Left].W)||
             (MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Right].W))
              MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint3L];
          else 
              MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint3R];
      }
      
      else if(type==GapHType)
      {
         PathBase.TransPointFlag=true;
         if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line1Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line1Left].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint1M];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line2Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line2Left].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint1M];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Left].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint3M];
      }
      
      else if(type==GapHFType)
      {
        PathBase.TransPointFlag=true;
         if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line1Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line1Right].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint1M];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line2Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line2Right].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint1M];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Right].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint3M];
      }
      
      else if(type==GapWType)
      {
        PathBase.TransPointFlag=true;
         if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Right].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint2R];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Middle].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Middle].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint2R];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Left].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint2L];
      }
         
      else if(type==GapWFType) 
      {
        PathBase.TransPointFlag=true;
         if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line1Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line1Right].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint2R];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line1Middle].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line1Middle].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint2R];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line1Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line1Left].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint2L];
      }
    }
  } 
}

