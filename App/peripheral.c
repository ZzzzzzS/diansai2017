#include "include.h"
#include "peripheral.h"
#include "stdlib.h"
#include "string.h"
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

    else if(hasData("L"))
    {
      char* i;
      i=strstr(buff,"L");
      path[CurrentPath].H=*(i+1);
      path[CurrentPath].W=*(i+2);
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
    else if(hasData("w"))
    {
      CurrentAimPosition.H+=5;
      printf("AimPosition %d %d\n",CurrentAimPosition.H,CurrentAimPosition.W);
    }
    else if(hasData("s"))
    {
      CurrentAimPosition.H-=5;
      printf("AimPosition %d %d\n",CurrentAimPosition.H,CurrentAimPosition.W);
    }
    else if(hasData("f"))
    {
      CurrentAimPosition.W+=5;
      printf("AimPosition %d %d\n",CurrentAimPosition.H,CurrentAimPosition.W);
    }
    else if(hasData("a"))
    {
      CurrentAimPosition.W-=5;
      printf("AimPosition %d %d\n",CurrentAimPosition.H,CurrentAimPosition.W);
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

/*============================================
函数名：OLED_Interface()
作用：OLED显示发车前界面
==========================================*/

void OLED_Interface()
{
	OLED_Print(Position(Line1), "HIT WH");
        OLED_Print(Position(Line1), "718Lab");
        OLED_Print(Position(Line1), "Untitled");
	OLED_Print(Position(Line4), "System Loading...");
}

/*============================================
函数名：DeBug_Interface()
作用：OLED显示调试时界面
==========================================*/

void DeBug_Interface()
{
  for(char i=0;i<CAMERA_H;i++)
    for(char j=0;j<CAMERA_W;j++)
    {
      if(img[i][j])
      {
        OLED_PutPixel(j, i);
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
        ServoBase[W].PidBase.PIDOutPosition=0;
        ServoBase[H].PidBase.PIDOutPosition=0;
        ControlOut();
	switch (Error_Number)
	{
	case Motor_Stop:
		OLED_Init();
		OLED_Print(Position(Line1), "motor error");
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
	/*if (Speed.Left.Out_Speed > Speed.Right.Out_Speed)
	{
		led(LED3, LED_ON);
		led(LED0, LED_OFF);
	}
	else if (Speed.Right.Out_Speed > Speed.Left.Out_Speed)
	{
		led(LED3, LED_OFF);
		led(LED0, LED_ON);
	}*/
}