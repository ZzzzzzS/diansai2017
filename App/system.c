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
  gpio_init(PTA8,GPO,0);
  while(!mpu6050_init());
  lptmr_timing_ms(10);
  set_vector_handler(LPTMR_VECTORn, MainLoop);
  EnableInterrupts;
  disable_irq(LPTMR_IRQn);
}

void GetSystemReady()
{
  
  DELAY_MS(1000);
  /*while(1)
  {
    printf("%d %d %d\n", mpu6050_ACCEL_X_data(), mpu6050_ACCEL_Y_data(),mpu6050_ACCEL_Z_data());
    
  }*/
  ResetGyro();
  CurrentAimPosition.H=AimPosition[Line1Right].H;
  CurrentAimPosition.W=AimPosition[Line1Right].W;
  ServoBase[W].PidBase.NowPosition=CurrentAimPosition.W;
  ServoBase[H].PidBase.NowPosition=CurrentAimPosition.H;
  MainBall.CurrentBallPosition=CurrentAimPosition;
  MainBall.LastBallPosition=CurrentAimPosition;
  OLED_Interface();
  OLED_CLS();
  enable_irq(LPTMR_IRQn);
}

void SystemUpdate()
{
  GetDeta();
  ConvertImg(img,imgFixed);
  //vcan_sendimg(imgbuff, sizeof(imgbuff));
  //vcan_sendimg(imgFixed, sizeof(imgFixed));
  if(1)
  {
  printf("position: %d %d  ",MainBall.CurrentBallPosition.H,MainBall.CurrentBallPosition.W);
  printf("Error %d %d  ",ServoBase[H].PidBase.ErrorPosition[Now_Error],ServoBase[W].PidBase.ErrorPosition[Now_Error]);
  printf("speed %d %d\n",MainBall.CurrentBallSpeed.H,MainBall.CurrentBallSpeed.W);
  }
  GetPosition();
  CalculatePosition();
  PIDControlPositional(&ServoBase[W]);
  PIDControlPositional(&ServoBase[H]);
  ControlOut();
}

void MainLoop()
{
  SetAimPosition();
  //AtPosition(CurrentAimPosition); 
  LPTMR_Flag_Clear();	
}