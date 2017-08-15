#include "include.h"
#include "system.h"

void MainLoop();

void SystemInit()
{
  DisableInterrupts;
  AimPositionInit();
  PIDInit();
  ControlInit();
  init_LED();
  OLED_Init();
  Init_Key();
  PathInit();
  UART_Init();
  //CheckInit();
  gpio_init(PTA8,GPO,0);
  //while(!mpu6050_init());
  lptmr_timing_ms(50);
  set_vector_handler(LPTMR_VECTORn, MainLoop);
  EnableInterrupts;
  disable_irq(LPTMR_IRQn);
}

void GetSystemReady()
{
  OLED_Print(Position(Line1),"正在水平校准");
  /*while(1)
  {
    printf("%d %d %d\n", mpu6050_ACCEL_X_data(), mpu6050_ACCEL_Y_data(),mpu6050_ACCEL_Z_data());
    
  }*/
  //ResetGyro();
  OLED_CLS();
  OLED_Print(Position(Line4),"校准完成");
  
  OLED_Interface();
 
  MainBall.CurrentAimPosition=PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter];
  MainBall.CurrentBallPosition.H=0;
  OLED_Print(Position(Line1),"系统准备就绪");
  OLED_Print(Position(Line2),"请放置小球");
  while(MainBall.CurrentBallPosition.H==0)
  {
    //GetDeta();
    ConvertImg(img,imgFixed);
    GetPosition();
  }
  OLED_CLS();
  OLED_Print(Position(Line1),"开始!");
  enable_irq(LPTMR_IRQn);
}

void SystemUpdate()
{
  //GetDeta();
  ConvertImg(img,imgFixed);
  //vcan_sendimg(imgbuff, sizeof(imgbuff));
  //vcan_sendimg(imgFixed, sizeof(imgFixed));
  if(0)
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
  if(PathBase.Function!=UserControl)
    SetAimPosition();
  LED_Interface();
  System_Interface();
  LPTMR_Flag_Clear();	
}