#include "include.h"
#include "PositionControl.h"
#include "data.h"
#include "math.h"

char GetType(position Aim,position Current)
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
  PathBase.AimPosition[Line3Left].H=89;
  PathBase.AimPosition[Line3Left].W=40;
  
  PathBase.AimPosition[Line3Middle].H=90;
  PathBase.AimPosition[Line3Middle].W=75;
  
  PathBase.AimPosition[Line3Right].H=90;
  PathBase.AimPosition[Line3Right].W=112;
  
  PathBase.AimPosition[Line2Left].H=53;
  PathBase.AimPosition[Line2Left].W=39;
  
  PathBase.AimPosition[Line2Middle].H=53;
  PathBase.AimPosition[Line2Middle].W=75;
  
  PathBase.AimPosition[Line2Right].H=53;
  PathBase.AimPosition[Line2Right].W=113;
  
  PathBase.AimPosition[Line1Left].H=16;
  PathBase.AimPosition[Line1Left].W=39;
  
  PathBase.AimPosition[Line1Middle].H=16;
  PathBase.AimPosition[Line1Middle].W=75;
  
  PathBase.AimPosition[Line1Right].H=17;
  PathBase.AimPosition[Line1Right].W=112;

  PathBase.AimPosition[TransPoint3L].H=70;
  PathBase.AimPosition[TransPoint3L].W=56;
    
  PathBase.AimPosition[TransPoint3R].H=65;
  PathBase.AimPosition[TransPoint3R].W=90;
    
  PathBase.AimPosition[TransPoint1L].H=41;
  PathBase.AimPosition[TransPoint1L].W=59;
    
  PathBase.AimPosition[TransPoint1R].H=42;
  PathBase.AimPosition[TransPoint1R].W=91;
  
  PathBase.AimPosition[TransPoint2R].H=54;
  PathBase.AimPosition[TransPoint2R].W=99;
  
  PathBase.AimPosition[TransPoint2L].H=54;
  PathBase.AimPosition[TransPoint2L].W=51;
  
  PathBase.AimPosition[TransPoint1M].H=28;
  PathBase.AimPosition[TransPoint1M].W=75;
  
  PathBase.AimPosition[TransPoint3M].H=75;
  PathBase.AimPosition[TransPoint3M].W=75;
  
}

void PathInit()
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

bool AtPositionNonBlocking(position base)
{
  if((ServoBase[W].PidBase.ErrorPosition[Now_Error]<7&&ServoBase[W].PidBase.ErrorPosition[Now_Error]>-7) && (ServoBase[H].PidBase.ErrorPosition[Now_Error]<7&&ServoBase[H].PidBase.ErrorPosition[Now_Error]>-7))
  {
    gpio_set(PTA8,1);
    return true;
  }
    gpio_set(PTA8,0);
    return false;
  
}

void SetAimPosition()
{
  if(PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter+1].H==0)
  {
    AtPosition(MainBall.CurrentAimPosition);
    return;
  }
  
  if(PathBase.Function==AdvanceFunction3)
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
  
  
  if(PathBase.TransPointFlag==true)
  {
    if(AtPositionNonBlocking(MainBall.CurrentAimPosition))
    {
      PathBase.TransPointFlag=false;
      PathBase.CurrentPositionCounter++;
      MainBall.CurrentAimPosition=PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter];
      
    }
  }
  else if(PathBase.TransPointFlag==false)
  {
    if(AtPosition(MainBall.CurrentAimPosition))
    {
      char type=GetType(MainBall.CurrentAimPosition,PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter+1]);
      
      if(type==BasicType)
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
      
      else if(type==GapWType)
      {
         PathBase.TransPointFlag=true;
         if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line1Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line1Left].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint1M];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line2Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line2Left].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint1M];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Left].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint3M];
      }
      
      else if(type==GapWFType)
      {
        PathBase.TransPointFlag=true;
         if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line1Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line1Right].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint1M];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line2Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line2Right].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint1M];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Right].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint3M];
      }
      
      else if(type==GapHType)
      {
        PathBase.TransPointFlag=true;
         if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Right].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Right].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint2R];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Middle].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Middle].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint2R];
         else if(MainBall.CurrentAimPosition.H==PathBase.AimPosition[Line3Left].H&&MainBall.CurrentAimPosition.W==PathBase.AimPosition[Line3Left].W)
           MainBall.CurrentAimPosition=PathBase.AimPosition[TransPoint2L];
      }
         
      else if(type==GapHFType) 
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