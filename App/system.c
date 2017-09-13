#include "include.h"
#include "system.h"

void MainLoop();

void SystemInit()
{
  DisableInterrupts;      //初始化前关闭所有中断(其实没必要)
  OLED_Init();
  AimPositionInit();
  PIDInit();
  ControlInit();
  OLED_Print(Position(Line2),"电机初始化完成");
  DELAY_MS(500);
  init_LED();
  Init_Key();
  PathInit();
  UART_Init();
  gpio_init(PTA8,GPO,0);
  while(!mpu6050_init()); //一直等待初始化
  OLED_Print(Position(Line3),"陀螺仪初始化完成");
  lptmr_timing_ms(50);    //设定中断时间
  set_vector_handler(LPTMR_VECTORn, MainLoop);//设定中断服务函数
  EnableInterrupts;
  disable_irq(LPTMR_IRQn);    //先关闭中断
  StepMotorInit();            //步进电机初始化
  OLED_CLS();
  OLED_Print(Position(Line1),"正在水平校准");
  ResetGyro();                //调整水平
  OLED_CLS();
  OLED_Print(Position(Line4),"校准完成");
  
  
  
}

void GetSystemReady()
{
  /*while(1)
  {
    printf("%d %d %d\n", mpu6050_ACCEL_X_data(), mpu6050_ACCEL_Y_data(),mpu6050_ACCEL_Z_data());
    
  }*/
  
  CheckInit();        //初始化摄像头,因为之前线不够长最后插入摄像头,所以摄像头初始化靠后
  OLED_Print(Position(Line1),"摄像头初始化完成");
  DELAY_MS(500);
  OLED_Interface();   //OLED选择模式
  OLED_CLS();
  MainBall.CurrentAimPosition=PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter];
  MainBall.CurrentBallPosition.H=0; //先把坐标置零
  OLED_Print(Position(Line1),"系统准备就绪");
  OLED_Print(Position(Line2),"请放置小球");
  while(MainBall.CurrentBallPosition.H==0)//检测坐标一直是零,证明一直没有放球,就一直等待
  {
    GetDeta();//采集图像
    ConvertImg(img,imgFixed);//变换图像
    GetPosition();//找到点的位置
  }
  OLED_CLS();
  OLED_Print(Position(Line1),"开始!");
  if(PathBase.Function==UserControl)//判断是自定义路径就再加一句提示的话
  {
    OLED_Print(Position(Line3),"请用触摸屏或蓝牙");
    OLED_Print(Position(Line4),"改变小球目标位置");
    MainBall.CurrentAimPosition=PathBase.AimPosition[Line2Middle];
  }
  enable_irq(LPTMR_IRQn);//开始允许中断,初始化完成
}

void SystemUpdate()
{
  GetDeta();//采集图像
  ConvertImg(img,imgFixed);//转换图像
  //vcan_sendimg(imgbuff, sizeof(imgbuff));//发送图像,山外上位机 
  //vcan_sendimg(imgFixed, sizeof(imgFixed));//发送图像,张晓冬上位机
  if(sendflag)//由蓝牙控制是否发送信息,默认不发送,也最好不要发送
  {
  printf("position: %d %d  ",MainBall.CurrentBallPosition.H,MainBall.CurrentBallPosition.W);
  printf("Error %d %d  ",ServoBase[H].PidBase.ErrorPosition[Now_Error],ServoBase[W].PidBase.ErrorPosition[Now_Error]);
  printf("speed %d %d\n",MainBall.CurrentBallSpeed.H,MainBall.CurrentBallSpeed.W);
  }
  GetPosition();//计算点坐标
  CalculatePosition();//计算点误差
  PIDControlPositional(&ServoBase[W]);//PID控制W轴
  PIDControlPositional(&ServoBase[H]);//PID控制H轴
  ControlOut();//输出到舵机
}

void MainLoop()
{
  if(PathBase.Function!=UserControl)//判断不是自定义路径就自动设定路径
    SetAimPosition();//设定路径
  LED_Interface();  //led灯显示,没什么用
  if(PathBase.Function==UserControl)//如果是自定义路径就接收触摸屏信息
  {
    GetRemoteControl();//接收遥控器
    GetTouch();//接收触摸屏
  }
  System_Interface();//OLED显示界面
  LPTMR_Flag_Clear();//清中断标志位
}