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
  //DELAY_MS(2000);
  OLED_CLS();
  enable_irq(LPTMR_IRQn);
}

void SystemUpdate()
{
  GetDeta();
  //vcan_sendimg(img, sizeof(img));
  printf("position: %d %d\n",MainBall.CurrentBallPosition.H,MainBall.CurrentBallPosition.W);
  //DeBug_Interface();//��Ҫˢͼ��ˢͼ̫��
  
}

void MainLoop()
{
  GetPosition();
  SetAimPosition();
  CalculatePosition();
  PIDControlPositional(&ServoBase[W]);
  PIDControlPositional(&ServoBase[H]);
  ControlOut();
  LPTMR_Flag_Clear();	
}