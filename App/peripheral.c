#include "include.h"
#include "peripheral.h"
#include "stdlib.h"
#include "string.h"

void AdvanceFunction2ConfigInterface();

char button[6]={0xB1,0xB2,0xB3,0xB4,0xB5,0xB6};

/*============================================
函数名：Receive_Data()
作用：蓝牙串口接收
==========================================*/
void uart4_handler(void)
{
    static char buff[10];
    static char count=0;
    if(uart_query    (UART4) == 1)   //接收数据寄存器满
    {
        //用户需要处理接收数据
        uart_getchar   (UART4, buff+count);
        count++;
        if(count==8)
          count=0;
    }
    
    
    if (hasData("STOP"))
    {
      System_Error(user_Stop);
    }
    
    else if(hasData("P"))
    {
      ServoBase[W].PidBase.PSet++;
      ServoBase[H].PidBase.PSet++;
      printf("Current P%d\n",(int)ServoBase[W].PidBase.PSet);
      count=0;
      memset(buff,0,sizeof(buff));
    }
    else if(hasData("p"))
    {
      ServoBase[H].PidBase.PSet--;
      ServoBase[W].PidBase.PSet--;
      printf("Current P%d\n",(int)ServoBase[H].PidBase.PSet);
      count=0;
      memset(buff,0,sizeof(buff));
    }
    else if(hasData("D"))
    {
      ServoBase[W].PidBase.DSet+=5;
      ServoBase[H].PidBase.DSet+=5;
      printf("Current D%d\n",(int)ServoBase[W].PidBase.DSet);
      count=0;
      memset(buff,0,sizeof(buff));
    }
    else if(hasData("d"))
    {
      ServoBase[H].PidBase.DSet-=5;
      ServoBase[W].PidBase.DSet-=5;
      printf("Current D%d\n",(int)ServoBase[H].PidBase.DSet);
      count=0;
      memset(buff,0,sizeof(buff));
    }
    else if(hasData("H"))
    {
      sendflag=1;
      count=0;
      memset(buff,0,sizeof(buff));
    }
    else if(hasData("h"))
    {
      sendflag=0;
      count=0;
      memset(buff,0,sizeof(buff));
    }
    else if(hasData("w"))
    {
      printf("ok");
      if(PathBase.Function==UserControl)
      {
        KeyState=Key1Down;
      }
      count=0;
      memset(buff,0,sizeof(buff));
    }
    else if(hasData("s"))
    {
      printf("ok");
      if(PathBase.Function==UserControl)
      {
        KeyState=Key4Down;
      }
      count=0;
      memset(buff,0,sizeof(buff));
    }
    else if(hasData("a"))
    {
      printf("ok");
      if(PathBase.Function==UserControl)
      {
        KeyState=Key2Down;
      }
      count=0;
      memset(buff,0,sizeof(buff));
    }
    else if(hasData("f"))
    {
      printf("ok");
      if(PathBase.Function==UserControl)
      {
        KeyState=Key3Down;
      }
      count=0;
      memset(buff,0,sizeof(buff));
    }
        
          
}

void UART_Init()
{
  uart_init(VCAN_PORT,VCAN_BAUD);
  set_vector_handler(UART4_RX_TX_VECTORn,uart4_handler);
  uart_rx_irq_en (UART4);
}
/*============================================
函数名：Key_Init()
作用：初始化按键
==========================================*/

void Init_Key()
{
  gpio_init(Key1, GPI, 0);
  gpio_init(Key2, GPI, 0);
  gpio_init(Key3, GPI, 0);
  gpio_init(Key4, GPI, 0);
}

void PushButtonUsersCallBack(PTXn_e ptxn)
{
  printf("OK");
  
  
}

/*============================================
函数名：OLED_Interface()
作用：OLED显示发车前界面
==========================================*/

void OLED_Interface()
{
  OLED_CLS();
  OLED_Print(Position(Line1), "DianSai2017");
  OLED_Print(Position(Line2), "718实验室");
  OLED_Print(Position(Line3), "当前路径:");
  //OLED_Print(Position(Line4), "基本1");
  /*PathBase.Function=UserControl;
  PathBase.StoredPath[UserControl][0]=PathBase.AimPosition[Line1Left];
  PathBase.StoredPath[UserControl][1]=PathBase.AimPosition[Line2Left];
  PathBase.StoredPath[UserControl][2]=PathBase.AimPosition[Line3Right];
  PathBase.StoredPath[UserControl][3]=PathBase.AimPosition[Line1Middle];
  PathBase.StoredPath[UserControl][4]=PathBase.AimPosition[Line3Middle];
  PathBase.StoredPath[UserControl][5]=PathBase.AimPosition[Line1Right];
  PathBase.StoredPath[UserControl][6]=PathBase.AimPosition[Line3Left];*/
  while(true)
  {
    DELAY_MS(20);
    switch(PathBase.Function)
    {
    case BasicFunction1:
      OLED_Print(Position(Line4), "基本功能1");
      break;
      
    case BasicFunction2:
      OLED_Print(Position(Line4), "基本功能2");
      break;
      
    case BasicFunction3:
      OLED_Print(Position(Line4), "基本功能3");
      break;
      
    case BasicFunction4:
      OLED_Print(Position(Line4), "基本功能4");
      break;
      
    case AdvanceFunction1:
      OLED_Print(Position(Line4), "发挥功能1");
      break;
      
    case AdvanceFunction2:
      OLED_Print(Position(Line4), "发挥功能2");
      break;
      
    case AdvanceFunction3:
      OLED_Print(Position(Line4), "发挥功能3");
      break;
      
    case UserControl:
      OLED_Print(Position(Line4), "自定路径 ");
      break;
    }
    
    if(gpio_get(Key1))
    {
      DELAY_MS(10);
      if(gpio_get(Key1))
      {
        PathBase.Function++;
        if(PathBase.Function==MAXFunction)
          PathBase.Function--;
       while(gpio_get(Key1)); 
      }
    }
    
    if(gpio_get(Key2))
    {
      DELAY_MS(10);
      if(gpio_get(Key2))
      {
        PathBase.Function--;
        if(PathBase.Function<BasicFunction1)
          PathBase.Function++;
        while(gpio_get(Key2));
      }
    }
    
    if(gpio_get(Key3))
    {
      DELAY_MS(10);
      if(gpio_get(Key3))
      {
        if(PathBase.Function==AdvanceFunction2)
        {
          while(gpio_get(Key3));
          AdvanceFunction2ConfigInterface();
        }
        while(gpio_get(Key3));
        return;
      }
    }
  }
}


void AdvanceFunction2ConfigInterface()
{
  char count=0;
  char temp[10];
  char NowPosition=0;
  OLED_CLS();
  OLED_Print(Position(Line1), "路径");
  OLED_Print(Position(Line3), "当前点");
  while(true)
  {
    sprintf(temp,"%d",count);
    OLED_Print(Position(Line2), temp);
    
    switch(NowPosition)
    {
    case 0:
      OLED_Print(Position(Line4), "1号点");
      PathBase.StoredPath[AdvanceFunction2][count]=PathBase.AimPosition[Line1Left];
      break;
      
    case 1:
      OLED_Print(Position(Line4), "2号点");
      PathBase.StoredPath[AdvanceFunction2][count]=PathBase.AimPosition[Line1Middle];
      break;
      
    case 2:
      OLED_Print(Position(Line4), "3号点");
      PathBase.StoredPath[AdvanceFunction2][count]=PathBase.AimPosition[Line1Right];
      break;
      
    case 3:
      OLED_Print(Position(Line4), "4号点");
      PathBase.StoredPath[AdvanceFunction2][count]=PathBase.AimPosition[Line2Left];
      break;
      
    case 4:
      OLED_Print(Position(Line4), "5号点");
      PathBase.StoredPath[AdvanceFunction2][count]=PathBase.AimPosition[Line2Middle];
      break;
      
    case 5:
      OLED_Print(Position(Line4), "6号点");
      PathBase.StoredPath[AdvanceFunction2][count]=PathBase.AimPosition[Line2Right];
      break;
      
    case 6:
      OLED_Print(Position(Line4), "7号点");
      PathBase.StoredPath[AdvanceFunction2][count]=PathBase.AimPosition[Line3Left];
      break;
      
    case 7:
      OLED_Print(Position(Line4), "8号点");
      PathBase.StoredPath[AdvanceFunction2][count]=PathBase.AimPosition[Line3Middle];
      break;
      
    case 8:
      OLED_Print(Position(Line4), "9号点");
      PathBase.StoredPath[AdvanceFunction2][count]=PathBase.AimPosition[Line3Right];
      break;
      
    default:
      NowPosition=0;
      break;
    }
    
    
    if(gpio_get(Key1))
    {
      DELAY_MS(10);
      if(gpio_get(Key1))
      {
        NowPosition++;
        if(NowPosition>8)
          NowPosition=8;
        while(gpio_get(Key1));
      }
    }
    
    if(gpio_get(Key2))
    {
      DELAY_MS(10);
      if(gpio_get(Key2))
      {
        NowPosition--;
        if(NowPosition<0)
          NowPosition=0;
        while(gpio_get(Key2));
      }
    }
    
    if(gpio_get(Key3))
    {
      DELAY_MS(20);
      if(gpio_get(Key3))
      {
        count++;
        while(gpio_get(Key3));
      }
      
    }
    
    if(gpio_get(Key4))
    {
      DELAY_MS(10);
      if(gpio_get(Key4))
      {
        while(gpio_get(Key4));
        return;
      }
    }
  }
}
/*============================================
函数名：DeBug_Interface()
作用：OLED显示调试时界面
==========================================*/

void System_Interface()
{
  char temp[20];
  sprintf(temp, "当前位置:%d %d ",MainBall.CurrentBallPosition.H,MainBall.CurrentBallPosition.W);
  OLED_Print(Position(Line1), temp);
  sprintf(temp, "目标位置:%d %d ",MainBall.CurrentAimPosition.H,MainBall.CurrentAimPosition.W);
  OLED_Print(Position(Line2), temp);
  if(PathBase.Function!=UserControl)
  {
    sprintf(temp, "当前用时:%d",MainBall.AimTime.S);
    OLED_Print(Position(Line3), temp);
    sprintf(temp, "总共用时:%d",MainBall.AllTime.S);
    OLED_Print(Position(Line4), temp);
  }
  
  if(gpio_get(Key4))
    {
      DELAY_MS(10);
      if(gpio_get(Key4))
      {
        OLED_CLS();
        OLED_Print(Position(Line4), "正在重置...");
        while(gpio_get(Key4));
        SystemReset();
      }
      
    }
  
  if(gpio_get(Key1))
    {
      DELAY_MS(10);
      if(gpio_get(Key1))
      {
        OLED_CLS();
        OLED_Print(Position(Line4), "正在重置...");
        while(gpio_get(Key1));
        SystemShutDown();
      }
      
    }
  
  if(PathBase.Function==UserControl)
  {
    switch(KeyState)
    {
    case Key1Down:
      if(MainBall.CurrentAimPosition.PositionNumber>=Line2Left)
        MainBall.CurrentAimPosition=PathBase.AimPosition[MainBall.CurrentAimPosition.PositionNumber-3];
      KeyState=KeyUp;
      break;
      
    case Key2Down:
      if(MainBall.CurrentAimPosition.PositionNumber!=Line1Left)
        MainBall.CurrentAimPosition=PathBase.AimPosition[MainBall.CurrentAimPosition.PositionNumber-1];
      KeyState=KeyUp;
      break;
      
    case Key3Down:
      if(MainBall.CurrentAimPosition.PositionNumber!=Line3Right)
        MainBall.CurrentAimPosition=PathBase.AimPosition[MainBall.CurrentAimPosition.PositionNumber+1];
      KeyState=KeyUp;
      break;
      
    case Key4Down:
      if(MainBall.CurrentAimPosition.PositionNumber<=Line2Right)
        MainBall.CurrentAimPosition=PathBase.AimPosition[MainBall.CurrentAimPosition.PositionNumber+3];
      KeyState=KeyUp;
      break;
      
    }
    
    switch(RemoteKeyState)
    {
    case Key1Down:
      if(MainBall.CurrentAimPosition.PositionNumber>=Line2Left)
        MainBall.CurrentAimPosition=PathBase.AimPosition[MainBall.CurrentAimPosition.PositionNumber-3];
      RemoteKeyState=KeyUp;
      break;
      
    case Key2Down:
      if(MainBall.CurrentAimPosition.PositionNumber!=Line1Left)
        MainBall.CurrentAimPosition=PathBase.AimPosition[MainBall.CurrentAimPosition.PositionNumber-1];
      RemoteKeyState=KeyUp;
      break;
      
    case Key3Down:
      if(MainBall.CurrentAimPosition.PositionNumber!=Line3Right)
        MainBall.CurrentAimPosition=PathBase.AimPosition[MainBall.CurrentAimPosition.PositionNumber+1];
      RemoteKeyState=KeyUp;
      break;
      
    case Key4Down:
      if(MainBall.CurrentAimPosition.PositionNumber<=Line2Right)
        MainBall.CurrentAimPosition=PathBase.AimPosition[MainBall.CurrentAimPosition.PositionNumber+3];
      RemoteKeyState=KeyUp;
      break;
      
    }
    
  }
}

/*============================================
函数名：System_Error(error Error_Number)
作用：调试模式系统错误紧急停车
==========================================*/

void System_Error(char Error_Number)
{
	disable_irq(LPTMR_IRQn);
        ServoBase[W].PidBase.PIDOutPosition=ServoBase[W].Middle;
        ServoBase[H].PidBase.PIDOutPosition=ServoBase[H].Middle;
        ControlOut();
	switch (Error_Number)
	{
	case PathFinish:
		OLED_Init();
		OLED_Print(Position(Line1), "到达终点");
		break;

	case Taget_Lost:
		OLED_Init();
		OLED_Print(Position(Line1), "Taget Lost");
		break;

	case Car_Stop:
		OLED_Init();
		OLED_Print(Position(Line1), "terminal point");
		break;

	case No_Mode:
		OLED_Init();
		OLED_Print(Position(Line1), "Mode Error");
		break;

	case user_Stop:
		OLED_Init();
		OLED_Print(Position(Line1), "user stop");
		OLED_Print(Position(Line2), "the Car");
		break;

	case hardfault:
		OLED_Init();
		OLED_Print(Position(Line1), "hardfault");
		OLED_Print(Position(Line2), "error");
		OLED_Print(Position(Line3), "restart system");
		break;

	default:
		OLED_Init();
		OLED_Print(Position(Line1), "Unknown Error");
		break;
	}

	while (!gpio_get(Key1));
	DELAY_MS(10);
	while (!gpio_get(Key1));
	enable_irq(LPTMR_IRQn);
}

/*============================================
函数名：init_LED()
作用：LED初始化函数
==========================================*/

void init_LED()
{
	led_init(LED0);
	led_init(LED1);
	led_init(LED2);
	led_init(LED3);
}

/*============================================
函数名：LED_Interface()
作用：LED显示函数
==========================================*/

void LED_Interface()
{
	
}

void ResetGyro()
{
  int16 yData;
  int16 xData;
  while(1)
  {
    yData=mpu6050_ACCEL_Y_data();
    xData=mpu6050_ACCEL_X_data();
    DELAY_MS(25);
    if(yData>-50)
      ServoBase[W].Middle--;
    else if(yData<-100)
      ServoBase[W].Middle++;
    
    if(xData>290)
      ServoBase[H].Middle--;
    else if(xData<230)
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
    if((yData<-50)&&(yData>-100) && (xData<290)&&(xData>230))
    {
      printf("MPU6050 OK!\n");
      break;
    }
  }
  ftm_pwm_duty(Servo_FTM, Servo_W_FTM, 300);
  DELAY_MS(30);
  ftm_pwm_duty(Servo_FTM, Servo_W_FTM, 1080);
  DELAY_MS(30);
  ftm_pwm_duty(Servo_FTM, Servo_W_FTM, ServoBase[W].Middle);
  
}

void SystemReset()
{
  disable_irq(LPTMR_IRQn);
  MainBall.AimTime.MS=0;
  MainBall.AllTime.S=0;
  MainBall.AimTime.S=0;
  MainBall.AllTime.MS=0;
  MainBall.CurrentBallPosition.H=0;
  MainBall.CurrentBallPosition.W=0;
  MainBall.LastBallPosition.H=0;
  MainBall.LastBallPosition.W=0;
  PathBase.CurrentPositionCounter=0;
  PathBase.TransPointFlag=false;
  PathBase.Function=BasicFunction1;
  GetSystemReady();
}

void TimeAddMS(time Base,int16 MS)
{
  Base.MS+=MS;
  
  if(Base.MS>1000)
  {
    Base.S+=Base.MS/1000;
    Base.MS%=1000;
  }
}

void GetTouch()
{
  touchposition temp=GetCurrentPosition();
  static char Key=KeyUp;
  if(temp.x<150&&temp.x>70&&temp.y<120&&temp.y>26)
  {
    MainBall.CurrentAimPosition.W=(150-temp.x)*1.2+30;
    MainBall.CurrentAimPosition.H=(120-temp.y)*1;
    MainBall.CurrentAimPosition.PositionNumber=Line2Middle;
  }
  
  if(temp.x<150&&temp.x>130&&temp.y<180&&temp.y>150)
  {
    Key=Key1Down;
  }
  else if(temp.x<120&&temp.x>90&&temp.y<148&&temp.y>130)
  {
    Key=Key2Down;
  }
  else if(temp.x<120&&temp.x>90&&temp.y<185&&temp.y>180)
  {
    Key=Key3Down;
  }
  else if(temp.x<80&&temp.x>60&&temp.y<180&&temp.y>150)
  {
    Key=Key4Down;
  }
  else
  {
    if(Key==Key1Down)
      KeyState=Key1Down;
    if(Key==Key2Down)
      KeyState=Key2Down;
    if(Key==Key3Down)
      KeyState=Key3Down;
    if(Key==Key4Down)
      KeyState=Key4Down;
    Key=KeyUp;
  }
}

void GetRemoteControl()
{
  static char Key=KeyUp;
  if(gpio_get(RemoteKey1))
  {
    printf("ok1\n");
    Key=Key1Down;
  }
  else if(gpio_get(RemoteKey2))
  {
    printf("ok2\n");
    Key=Key2Down;
  }
  else if(gpio_get(RemoteKey3))
  {
    printf("ok3\n");
    Key=Key3Down;
  }
  else if(gpio_get(RemoteKey4))
  {
    printf("ok4\n");
    Key=Key4Down;
  }
  else
  {
    if(Key==Key1Down)
      RemoteKeyState=Key1Down;
    if(Key==Key2Down)
      RemoteKeyState=Key2Down;
    if(Key==Key3Down)
      RemoteKeyState=Key3Down;
    if(Key==Key4Down)
      RemoteKeyState=Key4Down;
    Key=KeyUp;
    
  }
  
}

void RemoteControlInit()
{
  gpio_init(RemoteKey1, GPI, 0);
  gpio_init(RemoteKey2, GPI, 0);
  gpio_init(RemoteKey3, GPI, 0);
  gpio_init(RemoteKey4, GPI, 0);
  port_init_NoALT(RemoteKey1,PULLDOWN);
  port_init_NoALT(RemoteKey2,PULLDOWN);
  port_init_NoALT(RemoteKey3,PULLDOWN);
  port_init_NoALT(RemoteKey4,PULLDOWN);
  
}

void StepMotorInit()
{
  OLED_Print(Position(Line4),"正在载入");
  gpio_init(PTA5,GPO,1);
  gpio_init(PTA6,GPO,0);
  ftm_pwm_init(FTM0, FTM_CH4,200, 80); 
  while(!gpio_get(Key1));
  gpio_set(PTA5,0);
  OLED_CLS();
  OLED_Print(Position(Line4),"正在加载...");
  DELAY_MS(1000);
  /*ftm_pwm_init(FTM1, FTM_CH0,50, 53); 
  DELAY_MS(20);
  DELAY_MS(20);
  ftm_pwm_duty(FTM1, FTM_CH0, 60);
  DELAY_MS(20);
  DELAY_MS(20);
  ftm_pwm_duty(FTM1, FTM_CH0, 65);
  DELAY_MS(20);
  DELAY_MS(20);
  ftm_pwm_duty(FTM1, FTM_CH0, 70);
  DELAY_MS(20);
  DELAY_MS(20);
  ftm_pwm_duty(FTM1, FTM_CH0, 75);
  DELAY_MS(20);
  DELAY_MS(20);
  ftm_pwm_duty(FTM1, FTM_CH0, 80);*/
}
void SystemShutDown()
{
  disable_irq(LPTMR_IRQn);
  OLED_Print(Position(Line1),"正在关闭");
  gpio_init(PTA5,GPO,1);
  gpio_init(PTA6,GPO,1);
  ftm_pwm_init(FTM0, FTM_CH4,200, 80); 
  while(!gpio_get(Key4));
  gpio_set(PTA5,0);
  DELAY_MS(1000);
  /*ftm_pwm_init(FTM1, FTM_CH0,50, 75); 
  DELAY_MS(20);
  DELAY_MS(20);
  ftm_pwm_duty(FTM1, FTM_CH0, 70);
  DELAY_MS(20);
  DELAY_MS(20);
  ftm_pwm_duty(FTM1, FTM_CH0, 65);
  DELAY_MS(20);
  DELAY_MS(20);
  ftm_pwm_duty(FTM1, FTM_CH0, 60);
  DELAY_MS(20);
  DELAY_MS(20);
  ftm_pwm_duty(FTM1, FTM_CH0, 53);*/
  OLED_CLS();
  
}