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
  OLED_Interface();											//�����û�����
  OLED_CLS();
  enable_irq(LPTMR_IRQn);
}

void SystemUpdate()
{
  GetDeta();
  ConvertImg(img,imgFixed);
  //vcan_sendimg(imgbuff, sizeof(imgbuff));
  //vcan_sendimg(imgFixed, sizeof(imgFixed));
  if(sendflag)
  {
  printf("position: %d %d  ",MainBall.CurrentBallPosition.H,MainBall.CurrentBallPosition.W);
  printf("Error %d %d  ",ServoBase[H].PidBase.ErrorPosition[Now_Error],ServoBase[W].PidBase.ErrorPosition[Now_Error]);
  printf("speed %d %d\n",MainBall.CurrentBallSpeed.H,MainBall.CurrentBallSpeed.W);
  }
  GetPosition();
  /*SetAimPosition();
  CalculatePosition();
  PIDControlPositional(&ServoBase[W]);
  PIDControlPositional(&ServoBase[H]);
  ControlOut();*/
  
  
}

void MainLoop()
{
    //GetPosition();
    SetAimPosition();
    CalculatePosition();
    PIDControlPositional(&ServoBase[W]);
    PIDControlPositional(&ServoBase[H]);
    ServoBase[W].OutPosition=ServoBase[W].PidBase.PIDOutPosition;
    ServoBase[H].OutPosition=ServoBase[H].PidBase.PIDOutPosition;
    ControlOut();
  
    LPTMR_Flag_Clear();	
}