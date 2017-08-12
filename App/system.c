#include "include.h"
#include "system.h"

void MainLoop();

void SystemInit()
{
  DisableInterrupts;
  PIDInit();
  ControlInit();
  OLED_Init();
  Init_Key();
  PathInit();
  UART_Init();
  CheckInit();
  lptmr_timing_ms(20);
  set_vector_handler(LPTMR_VECTORn, MainLoop);
  EnableInterrupts;
  disable_irq(LPTMR_IRQn);
}

void GetSystemReady()
{
  CurrentAimPosition=AimPosition[Line2Middle];
  ServoBase[W].PidBase.NowPosition=CurrentAimPosition.W;
  ServoBase[H].PidBase.NowPosition=CurrentAimPosition.H;
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
  //printf("position: %d %d\n",MainBall.CurrentBallPosition.H,MainBall.CurrentBallPosition.W);
  //printf("Error %d %d\n",ServoBase[H].PidBase.ErrorPosition[Now_Error],ServoBase[W].PidBase.ErrorPosition[Now_Error]);
  GetPosition();
  SetAimPosition();
  CalculatePosition();
  PIDControlPositional(&ServoBase[W]);
  PIDControlPositional(&ServoBase[H]);
  ControlOut();
  
  
}

void MainLoop()
{
  /*GetPosition();
  SetAimPosition();
  CalculatePosition();
  PIDControlPositional(&ServoBase[W]);
  PIDControlPositional(&ServoBase[H]);
  ControlOut();*/
  LPTMR_Flag_Clear();	
}