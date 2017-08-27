#ifndef DATA_H__
#define DATA_H__

#include "common.h"
#include "include.h"
#include "VCAN_OV7725_Eagle.h"

/*============================================
位置和摄像头数据结构体
==========================================*/
#define StableRange 3    //圆边界大小,认为离中心点在这个范围内就认为到达点了
#define StableTimes 40   //在N周期内检测在范围内就认为稳定,40(周期)X50(毫秒/周期)=2秒

#define MAXW    125     //圈定采集的边界     -------> w轴
#define MINW    27       //                 |
#define MAXH    100     //                  |
#define MINH    1      //                   |H轴

//positionl结构体,储存横坐标,纵坐标,以及当前点是属于1~9号点的哪个点,此结构体非常重要
typedef struct          
{
  char H;
  char W;
  char PositionNumber;
}position;

//用于计时的结构体
typedef struct
{
  int16 S;
  int16 MS;
}time;

//枚举确定9个目标点和8个过渡点的位置
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
  
  TransPoint1L,
  TransPoint1R,
  TransPoint3L,
  TransPoint3R,
  
  TransPoint1M,
  TransPoint2L,
  TransPoint2R,
  TransPoint3M,
  
  MAX_Position
}Aim_Position;


//ball结构体,储存和球位置有关的信息
typedef struct
{
  position CurrentBallPosition;     //球当前位置信息
  position LastBallPosition;        //上一帧球的位置信息
  position CurrentBallSpeed;        //当前球的速度
  position LastBallSpeed;           //上一次球的速度
  position CurrentAimPosition;      //当前的目标点
  time AllTime;                     //开机共用时
  time AimTime;                     //从上一个目标点到现在用时
}ball;

extern uint8 imgbuff[CAMERA_SIZE];         //定义存储接收图像的数组,未解压,山外上位机看这个,选择160*120,二值化图像
extern uint8 img[CAMERA_H][CAMERA_W];      //接收解压过的图像
extern uint8 imgFixed[CAMERA_H][CAMERA_W]; //矫正过的图像,张晓冬上位机看这个,选择160*120,灰度图像

extern ball MainBall;

/*============================================
路径控制结构体
==========================================*/
//枚举定义当前所选择的功能
typedef enum
{
  BasicFunction1, //基本功能1
  BasicFunction2,
  BasicFunction3,
  BasicFunction4,
  AdvanceFunction1,
  AdvanceFunction2,
  AdvanceFunction3,
  
  UserControl,  //自己设定路径,蓝牙控球,触摸控球就选这个
  
  MAXFunction
}function;

//枚举定义的道路类型,用于绕过障碍点
typedef enum 
{
  BasicType,    //普通类型,点相邻
  BiagonalType, //对角线类型
  GapWType,
  GapWFType,
  GapHType,
  GapHFType,
  
  MAXType
}RoadType;

//定义路径结构体,储存9+8点位置,储存好的路径,用户刚输入的路径等
typedef struct
{
  position AimPosition[20];   //储存9+8个点的位置
  char Function;              //储存当前所选择的功能
  position StoredPath[8][40]; //储存不同功能的路径
  unsigned char CurrentPositionCounter;
  unsigned char TransPointFlag; //标志位,判断是否在中间转移点上
}path;

extern path PathBase;

/*============================================
PID相关数据结构体
==========================================*/
typedef enum						//PID误差枚举
{
	Now_Error,
	last_Error,
	lastest_Error
}PID_Error;


//PID结构体,注意修改参数请修改PSet,修改P是无效的
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
//枚举定义舵机编号
typedef enum
{
  W,
  H,
  MAX
}servo_enum;

#define MAX_POSITION_W  1080    //定义舵机最大最小值
#define MAX_POSITION_H  1080
#define MIN_POSITION_W  300
#define MIN_POSITION_H  300

#define Servo_FTM FTM2          //定义舵机管脚
#define Servo_W_FTM FTM_CH1
#define Servo_H_FTM FTM_CH0
#define Serv0_HZ    50


//定义舵机类型结构体控制舵机
typedef struct
{
  pidbase PidBase;  //pid类型用于PID计算
  int OutPosition;  //最终输出到舵机上的PWM值
  int Middle;       //舵机中值
}servo;

extern servo ServoBase[2];

/*============================================
OLED显示相关定义
==========================================*/
						//OLED相关宏定义
#define DC	PTC13
#define RESET	PTC12						//OLED相关宏定义
#define D1	PTC9						//OLED相关宏定义
#define D0	PTC8						//OLED相关宏定义

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
#define RemoteKey1 PTE1
#define RemoteKey2 PTE0
#define RemoteKey3 PTE4
#define RemoteKey4 PTD13


extern char BlueToothReceiveAera[20];
#define   hasData(x)	strstr(buff,(x))!=NULL

typedef enum	
{
	PathFinish,
	Taget_Lost,
	Car_Stop,
	No_Mode,
	user_Stop,
	hardfault,

	MAX_error
}Error_Num;

typedef enum
{
  KeyUp=0x00,
  Key1Down=0x01,
  Key2Down=0x02,
  Key3Down=0x04,
  Key4Down=0x08,
  Key5Down=0x10,
  Key6Down=0x20,
  Key7Down=0x40,
  Key8Down=0x80
  
}KeyStates;



extern char sendflag;

extern volatile char KeyState;
extern volatile char RemoteKeyState;

extern void PIDControl(servo *Base);
extern bool AtPosition(position base);
extern void PIDControlPositional(servo *Base);
extern void SetPID(servo* Base);
extern void ConvertImg(uint8 image1[CAMERA_H][CAMERA_W], uint8 image2[CAMERA_H][CAMERA_W]);
extern bool AtPositionNonBlocking(position base);
extern void TimeAddMS(time Base,int16 MS);

#endif //DATA_H