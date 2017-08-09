#ifndef DATA_H
#define DATA_H

#include "common.h"
#include "include.h"
#include "VCAN_OV7725_Eagle.h"

/*============================================
λ�ú�����ͷ���ݽṹ��
==========================================*/
#define StableRange 5  //Բ�߽��С
#define StableTimes 5  //��N�����ڼ���ڷ�Χ�ھ���Ϊ�ȶ�

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

extern uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
extern uint8 img[CAMERA_H][CAMERA_W];
extern position CurrentAimPosition;
extern position AimPosition[9];
extern position path[9];
extern int CurrentPath;//��ǰλ��
extern ball MainBall;

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
	float P;												//pid����
	float I;												//pid����
	float D;												//pid����;
	int16 AimPosition;								//pidĿ���ٶ�
	int16 NowPosition;								//pid��ǰ�ٶ�
	int16 ErrorPosition[3];							//pid����ٶ�
	int16 IntergatePosition;						//��������ٶ�
	int16 IncrementPosition;						//�ٶ�����
	int16 PIDOutPosition;						//��������ٶ�
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


#define MAX_POSITION_W  100
#define MAX_POSITION_H  100
#define MIN_POSITION_W  0
#define MIN_POSITION_H  0

#define Servo_FTM FTM0
#define Servo_W_FTM FTM_CH1
#define Servo_H_FTM FTM_CH2
#define Serv0_HZ    50

typedef struct
{
  pidbase PidBase;
}servo;

extern servo ServoBase[2];

/*============================================
OLED��ʾ��ض���
==========================================*/
#define RESET	PTC14_OUT						//OLED��غ궨��
#define DC	PTC16_OUT						//OLED��غ궨��
#define D1	PTC12_OUT						//OLED��غ궨��
#define D0	PTC10_OUT						//OLED��غ궨��

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
#define Key1   PTC5		//�����ܽŶ���
#define Key2   PTC11		//�����ܽŶ���
#define Key3   PTC9		//�����ܽŶ���
#define Key4   PTC7		//�����ܽŶ���


extern char BlueToothReceiveAera[20];
#define   hasData(x)	strstr(BlueToothReceiveAera,(x))!=NULL

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



extern void PIDControl(servo *Base);
extern bool AtPosition(position base);

#endif //DATA_H