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
  lptmr_timing_ms(50);
  set_vector_handler(LPTMR_VECTORn, MainLoop);
  EnableInterrupts;
  disable_irq(LPTMR_IRQn);
}

void GetSystemReady()
{
  
  OLED_Print(Position(Line1),"GYRO Loading...");
  /*while(1)
  {
    printf("%d %d %d\n", mpu6050_ACCEL_X_data(), mpu6050_ACCEL_Y_data(),mpu6050_ACCEL_Z_data());
    
  }*/
  ResetGyro();
  OLED_CLS();
  OLED_Print(Position(Line1),"GYRO OK!");
  OLED_Interface();
  MainBall.CurrentAimPosition=PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter];
  MainBall.CurrentBallPosition.H=0;
  OLED_Print(Position(Line1),"System Ready!");
  while(MainBall.CurrentBallPosition.H==0)
  {
    GetDeta();
    ConvertImg(img,imgFixed);
    GetPosition();
  }
  OLED_CLS();
  OLED_Print(Position(Line1),"Start!");
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