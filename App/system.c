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
  while(!mpu6050_init());
  lptmr_timing_ms(50);
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
  int16 yData;
  int16 xData;
   while(1)
  {
    yData=mpu6050_ACCEL_Y_data();
    xData=mpu6050_ACCEL_X_data();
    DELAY_MS(50);
    if(yData>-20)
      ServoBase[W].Middle--;
    else if(yData<-70)
      ServoBase[W].Middle++;
    
    if(xData>730)
      ServoBase[H].Middle--;
    else if(xData<670)
      ServoBase[H].Middle++;
    
    if(ServoBase[W].Middle>=MAX_POSITION_W)
      ServoBase[W].Middle=MAX_POSITION_W;
    else if(ServoBase[W].Middle<=MIN_POSITION_W)
      ServoBase[W].Middle=MIN_POSITION_W;
  
    if(ServoBase[H].Middle>=MAX_POSITION_H)
      ServoBase[H].Middle=MAX_POSITION_H;
    else if(ServoBase[H].Middle<=MIN_POSITION_H)
      ServoBase[H].Middle=MIN_POSITION_H;
    
    ftm_pwm_duty(Servo_FTM, Servo_W_FTM, ServoBase[W].Middle);
    ftm_pwm_duty(Servo_FTM, Servo_H_FTM, ServoBase[H].Middle);
    printf("%d %d\n", xData, yData);
    if((yData<-20)&&(yData>-70) && (xData<730)&&(xData>670))
    {
      printf("MPU6050 OK!\n");
      break;
    }
    
  }
  //while(1){printf("%d %d\n", xData, yData);};
  CurrentAimPosition.H=AimPosition[Line1Right].H;
  CurrentAimPosition.W=AimPosition[Line1Right].W;
  ServoBase[W].PidBase.NowPosition=CurrentAimPosition.W;
  ServoBase[H].PidBase.NowPosition=CurrentAimPosition.H;
  MainBall.CurrentBallPosition=CurrentAimPosition;
  MainBall.LastBallPosition=CurrentAimPosition;
  OLED_Interface();											//设置用户参数
  OLED_CLS();
  enable_irq(LPTMR_IRQn);
}

void SystemUpdate()
{
  GetDeta();
  ConvertImg(img,imgFixed);
  //vcan_sendimg(imgbuff, sizeof(imgbuff));
  //vcan_sendimg(imgFixed, sizeof(imgFixed));
  printf("%d %d %d\n", mpu6050_ACCEL_X_data(), mpu6050_ACCEL_Y_data(),mpu6050_ACCEL_Y_data());
  printf("Mid%d %d",ServoBase[H].Middle,ServoBase[W].Middle);
  if(sendflag)
  {
  printf("position: %d %d  ",MainBall.CurrentBallPosition.H,MainBall.CurrentBallPosition.W);
  printf("Error %d %d  ",ServoBase[H].PidBase.ErrorPosition[Now_Error],ServoBase[W].PidBase.ErrorPosition[Now_Error]);
  printf("speed %d %d\n",MainBall.CurrentBallSpeed.H,MainBall.CurrentBallSpeed.W);
  }
  GetPosition();
  SetAimPosition();
  CalculatePosition();
  PIDControlPositional(&ServoBase[W]);
  PIDControlPositional(&ServoBase[H]);
  ControlOut();
  
  
}

void MainLoop()
{
    //GetPosition();
    /*SetAimPosition();
    CalculatePosition();
    PIDControlPositional(&ServoBase[W]);
    PIDControlPositional(&ServoBase[H]);
    ServoBase[W].OutPosition=ServoBase[W].PidBase.PIDOutPosition;
    ServoBase[H].OutPosition=ServoBase[H].PidBase.PIDOutPosition;
    ControlOut();*/
  
    LPTMR_Flag_Clear();	
}