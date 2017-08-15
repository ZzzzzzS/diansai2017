#ifndef DATA_H__
#define DATA_H__

#include "common.h"
#include "include.h"
#include "VCAN_OV7725_Eagle.h"

/*============================================
λ�ú�����ͷ���ݽṹ��
==========================================*/
#define StableRange 3  //Բ�߽��С
#define StableTimes 40  //��N�����ڼ���ڷ�Χ�ھ���Ϊ�ȶ�

#define MAXW    127
#define MINW    24
#define MAXH    105
#define MINH    0

typedef struct
{
  char H;
  char W;
}position;

typedef struct
{
  int16 S;
  int16 MS;
}time;


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

typedef struct
{
  position CurrentBallPosition;
  position LastBallPosition;
  position CurrentBallSpeed;
  position LastBallSpeed;
  position CurrentAimPosition;
  
  time AllTime;
  time AimTime;
}ball;

extern uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
extern uint8 img[CAMERA_H][CAMERA_W];
extern uint8 imgFixed[CAMERA_H][CAMERA_W];

extern ball MainBall;

/*============================================
·�����ƽṹ��
==========================================*/
typedef enum
{
  BasicFunction1,
  BasicFunction2,
  BasicFunction3,
  BasicFunction4,
  AdvanceFunction1,
  AdvanceFunction2,
  AdvanceFunction3,
  
  UserControl,
  
  MAXFunction
}function;

typedef enum
{
  BasicType,
  BiagonalType,
  GapWType,
  GapWFType,
  GapHType,
  GapHFType,
  
  MAXType
}RoadType;

typedef struct
{
  position AimPosition[20];
  char Function;
  position StoredPath[8][40];
  unsigned char CurrentPositionCounter;
  unsigned char TransPointFlag;
}path;

extern path PathBase;

/*============================================
PID������ݽṹ��
==========================================*/
typedef enum						//PID���ö��
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
  float P;												//pid����
  float I;												//pid����
  float D;												//pid����;
  int16 AimPosition;								//pidĿ���ٶ�
  int16 NowPosition;								//pid��ǰ�ٶ�
  int16 ErrorPosition[3];							//pid����ٶ�
  int16 IntergatePosition;						//��������ٶ�
  int16 IncrementPosition;						//�ٶ�����
  int16 PIDOutPosition;						//��������ٶ�
  int16 DeltaError;
}pidbase;

/*============================================
������ƽṹ��
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
OLED��ʾ��ض���
==========================================*/
						//OLED��غ궨��
#define DC	PTC13
#define RESET	PTC12						//OLED��غ궨��
#define D1	PTC9						//OLED��غ궨��
#define D0	PTC8						//OLED��غ궨��

#define Position(OLED_Line)		0,(OLED_Line)	//���궨��

typedef enum OLED_Line			//����OLED��ʾλ��
{
	Line1 = 0,
	Line2 = 2,
	Line3 = 4,
	Line4 = 6,

	MAX_Line
}OLED_Line;

/*============================================
�����ṹ��
==========================================*/

#define bool char
#define true  1
#define false 0
#define Key1   PTE26		//�����ܽŶ���
#define Key2   PTE25		//�����ܽŶ���
#define Key3   PTE24		//�����ܽŶ���
#define Key4   PTA9		//�����ܽŶ���


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

extern char sendflag;


extern void PIDControl(servo *Base);
extern bool AtPosition(position base);
extern void PIDControlPositional(servo *Base);
extern void SetPID(servo* Base);
extern void ConvertImg(uint8 image1[CAMERA_H][CAMERA_W], uint8 image2[CAMERA_H][CAMERA_W]);
extern bool AtPositionNonBlocking(position base);
extern void TimeAddMS(time Base,int16 MS);

#endif //DATA_H