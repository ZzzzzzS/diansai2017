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
  CheckInit();
  lptmr_timing_ms(20);
  set_vector_handler(LPTMR_VECTORn, MainLoop);
  EnableInterrupts;
  disable_irq(LPTMR_IRQn);
}

void GetSystemReady()
{
  OLED_Interface();											//�����û�����
  DELAY_MS(2000);
  OLED_CLS();
  enable_irq(LPTMR_IRQn);
}

void SystemUpdate()
{
  GetDeta();
  vcan_sendimg(imgbuff, sizeof(imgbuff));
  DeBug_Interface();
}

void MainLoop()
{
  GetPosition();
  SetAimPosition();
  CalculatePosition();
  PIDControl(&ServoBase[H]);
  PIDControl(&ServoBase[W]);
  ControlOut();
  LPTMR_Flag_Clear();	
}