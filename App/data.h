#ifndef DATA_H__
#define DATA_H__

#include "common.h"
#include "include.h"
#include "VCAN_OV7725_Eagle.h"

/*============================================
位置和摄像头数据结构体
==========================================*/
#define StableRange 3  //圆边界大小
#define StableTimes 180  //在N周期内检测在范围内就认为稳定

#define MAXW    127
#define MINW    24
#define MAXH    105
#define MINH    0

typedef struct
{
  char H;
  char W;
}position;

typedef enum
{
  Line1Left,
  Line1Middle,
  Line1Right,
  Line2Left,
  Line2Middle,
  Line2Right,
  Line3Left,
  Line3Middle,
  Line3Right,
  
  MAX_Position
}Aim_Position;

typedef struct
{
  position CurrentBallPosition;
  position LastBallPosition;
  position CurrentBallSpeed;
  position LastBallSpeed;
}ball;

extern uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
extern uint8 img[CAMERA_H][CAMERA_W];
extern uint8 imgFixed[CAMERA_H][CAMERA_W];
extern position CurrentAimPosition;
extern position AimPosition[9];
extern position path[9];
extern int CurrentPath;//当前位置
extern ball MainBall;

/*============================================
PID相关数据结构体
==========================================*/
typedef enum						//PID误差枚举
{
	Now_Error,
	last_Error,
	lastest_Error
}PID_Error;

typedef struct
{
  float PSet;
  float ISet;
  float DSet;
  float P;												//pid常量
  float I;												//pid常量
  float D;												//pid常量;
  int16 AimPosition;								//pid目标速度
  int16 NowPosition;								//pid当前速度
  int16 ErrorPosition[3];							//pid误差速度
  int16 IntergatePosition;						//定义积分速度
  int16 IncrementPosition;						//速度增量
  int16 PIDOutPosition;						//最终输出速度
  int16 DeltaError;
}pidbase;

/*============================================
舵机控制结构体
==========================================*/
typedef enum
{
  W,
  H,
  MAX
}servo_enum;


#define MAX_POSITION_W  1080
#define MAX_POSITION_H  1080
#define MIN_POSITION_W  300
#define MIN_POSITION_H  300

#define Servo_FTM FTM2
#define Servo_W_FTM FTM_CH1
#define Servo_H_FTM FTM_CH0
#define Serv0_HZ    50

typedef struct
{
  pidbase PidBase;
  int OutPosition;
  int Middle;
}servo;

extern servo ServoBase[2];

/*============================================
OLED显示相关定义
==========================================*/
						//OLED相关宏定义
#define DC	PTC3
#define RESET	PTC2						//OLED相关宏定义
#define D1	PTC1						//OLED相关宏定义
#define D0	PTC0						//OLED相关宏定义

#define Position(OLED_Line)		0,(OLED_Line)	//坐标定义

typedef enum OLED_Line			//定义OLED显示位置
{
	Line1 = 0,
	Line2 = 2,
	Line3 = 4,
	Line4 = 6,

	MAX_Line
}OLED_Line;

/*============================================
其他结构体
==========================================*/

#define bool char
#define true  1
#define false 0
#define Key1   PTE26		//按键管脚定义
#define Key2   PTE25		//按键管脚定义
#define Key3   PTE24		//按键管脚定义
#define Key4   PTA9		//按键管脚定义


extern char BlueToothReceiveAera[20];
#define   hasData(x)	strstr(buff,(x))!=NULL

typedef enum	
{
	Motor_Stop,
	Taget_Lost,
	Car_Stop,
	No_Mode,
	user_Stop,
	hardfault,

	MAX_error
}Error_Num;

extern char sendflag;


extern void PIDControl(servo *Base);
extern bool AtPosition(position base);
extern void PIDControlPositional(servo *Base);
extern void SetPID(servo* Base);
extern void ConvertImg(uint8 image1[CAMERA_H][CAMERA_W], uint8 image2[CAMERA_H][CAMERA_W]);

#endif //DATA_H