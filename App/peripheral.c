#include "include.h"
#include "peripheral.h"
#include "stdlib.h"
#include "string.h"

/*============================================
函数名：Receive_Data()
作用：蓝牙串口接收
==========================================*/


void Receive_Data()
{
	if (uart_querystr(VCAN_PORT, BlueToothReceiveAera, 19))
	{
          led(LED1, LED_ON);
          if (hasData("STOP"))
          {
            System_Error(user_Stop);
          }

          else if(hasData("L"))
          {
            char* i;
            i=strstr(BlueToothReceiveAera,"L");
            path[CurrentPath].H=*(i+1);
            path[CurrentPath].W=*(i+2);
          }
       else
       {
         printf("ERROR COMMAND\n");
       }  
		memset(BlueToothReceiveAera, 0, 20);		//清零数组防止一些奇怪的情况
	}
	else
		led(LED1, LED_OFF);
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