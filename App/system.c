#include "include.h"
#include "system.h"

void MainLoop();

void SystemInit()
{
  DisableInterrupts;
  AimPositionInit();
  PIDInit();
  ControlInit();
  OLED_Init();
  Init_Key();
  PathInit();
  UART_Init();
  CheckInit();
  lptmr_timing_ms(50);
  set_vector_handler(LPTMR_VECTORn, MainLoop);
  EnableInterrupts;
  disable_irq(LPTMR_IRQn);
}

void GetSystemReady()
{
  CurrentAimPosition.H=AimPosition[Line2Middle].H;
  CurrentAimPosition.W=AimPosition[Line2Middle].W;
  ServoBase[W].PidBase.NowPosition=CurrentAimPosition.W;
  ServoBase[H].PidBase.NowPosition=CurrentAimPosition.H;
  MainBall.CurrentBallPosition=CurrentAimPosition;
  MainBall.LastBallPosition=CurrentAimPosition;
  OLED_Interface();											//设置用户参数
  //DELAY_MS(2000);
  OLED_CLS();
  enable_irq(LPTMR_IRQn);
}

void SystemUpdate()
{
  GetDeta();
  //ConvertImg();
  //vcan_sendimg(imgbuff, sizeof(imgbuff));
  //vcan_sendimg(img, sizeof(img));
  printf("position: %d %d  ",MainBall.CurrentBallPosition.H,MainBall.CurrentBallPosition.W);
  printf("Error %d %d  ",ServoBase[H].PidBase.ErrorPosition[Now_Error],ServoBase[W].PidBase.ErrorPosition[Now_Error]);
  printf("speed %d %d\n",MainBall.CurrentBallSpeed.H,MainBall.CurrentBallSpeed.W);
  //GetPosition();
  /*SetAimPosition();
  CalculatePosition();
  PIDControlPositional(&ServoBase[W]);
  PIDControlPositional(&ServoBase[H]);
  ControlOut();*/
  
  
}

void MainLoop()
{
  static char count=0;
  switch(count)
  {
  case 0:
    GetPosition();
    SetAimPosition();
    CalculatePosition();
    PIDControlPositional(&ServoBase[W]);
    PIDControlPositional(&ServoBase[H]);
    ServoBase[W].OutPosition=ServoBase[W].PidBase.PIDOutPosition*0.33;
    ServoBase[H].OutPosition=ServoBase[H].PidBase.PIDOutPosition*0.33;
    ControlOut();
  case 1:
    ServoBase[W].OutPosition=ServoBase[W].PidBase.PIDOutPosition*0.66;
    ServoBase[H].OutPosition=ServoBase[H].PidBase.PIDOutPosition*0.66;
    ControlOut();
  case 2:
    ServoBase[W].OutPosition=ServoBase[W].PidBase.PIDOutPosition;
    ServoBase[H].OutPosition=ServoBase[H].PidBase.PIDOutPosition;
    ControlOut();
    
  }
  count++;
  if(count>=3)
    count=0;
  
  
  LPTMR_Flag_Clear();	
}