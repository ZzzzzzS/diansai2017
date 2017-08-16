#include "include.h"
#include "system.h"

void MainLoop();

void SystemInit()
{
  DisableInterrupts;
  OLED_Init();
  //CheckInit();
  OLED_Print(Position(Line1),"摄像头初始化完成");
  AimPositionInit();
  PIDInit();
  ControlInit();
  OLED_Print(Position(Line2),"电机初始化完成");
  init_LED();
  Init_Key();
  PathInit();
  UART_Init();
  gpio_init(PTA8,GPO,0);
  //while(!mpu6050_init());
  OLED_Print(Position(Line2),"陀螺仪初始化完成");
  lptmr_timing_ms(50);
  set_vector_handler(LPTMR_VECTORn, MainLoop);
  EnableInterrupts;
  disable_irq(LPTMR_IRQn);
  OLED_Print(Position(Line1),"正在水平校准");
  //ResetGyro();
  OLED_CLS();
  OLED_Print(Position(Line4),"校准完成");
  
  
  
}

void GetSystemReady()
{
  /*while(1)
  {
    printf("%d %d %d\n", mpu6050_ACCEL_X_data(), mpu6050_ACCEL_Y_data(),mpu6050_ACCEL_Z_data());
    
  }*/
  
  
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
  if(PathBase.Function==UserControl)
  {
    OLED_Print(Position(Line3),"请用触摸屏或蓝牙");
    OLED_Print(Position(Line4),"改变小球目标位置");
  }
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
  if(PathBase.Function==UserControl)
  {
    //GetRemoteControl();
    GetTouch();
  }
  System_Interface();
  LPTMR_Flag_Clear();	
}