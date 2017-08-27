#ifndef DATA_H__
#define DATA_H__

#include "common.h"
#include "include.h"
#include "VCAN_OV7725_Eagle.h"

/*============================================
λ�ú�����ͷ���ݽṹ��
==========================================*/
#define StableRange 3    //Բ�߽��С,��Ϊ�����ĵ��������Χ�ھ���Ϊ�������
#define StableTimes 40   //��N�����ڼ���ڷ�Χ�ھ���Ϊ�ȶ�,40(����)X50(����/����)=2��

#define MAXW    125     //Ȧ���ɼ��ı߽�     -------> w��
#define MINW    27       //                 |
#define MAXH    100     //                  |
#define MINH    1      //                   |H��

//positionl�ṹ��,���������,������,�Լ���ǰ��������1~9�ŵ���ĸ���,�˽ṹ��ǳ���Ҫ
typedef struct          
{
  char H;
  char W;
  char PositionNumber;
}position;

//���ڼ�ʱ�Ľṹ��
typedef struct
{
  int16 S;
  int16 MS;
}time;

//ö��ȷ��9��Ŀ����8�����ɵ��λ��
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


//ball�ṹ��,�������λ���йص���Ϣ
typedef struct
{
  position CurrentBallPosition;     //��ǰλ����Ϣ
  position LastBallPosition;        //��һ֡���λ����Ϣ
  position CurrentBallSpeed;        //��ǰ����ٶ�
  position LastBallSpeed;           //��һ������ٶ�
  position CurrentAimPosition;      //��ǰ��Ŀ���
  time AllTime;                     //��������ʱ
  time AimTime;                     //����һ��Ŀ��㵽������ʱ
}ball;

extern uint8 imgbuff[CAMERA_SIZE];         //����洢����ͼ�������,δ��ѹ,ɽ����λ�������,ѡ��160*120,��ֵ��ͼ��
extern uint8 img[CAMERA_H][CAMERA_W];      //���ս�ѹ����ͼ��
extern uint8 imgFixed[CAMERA_H][CAMERA_W]; //��������ͼ��,��������λ�������,ѡ��160*120,�Ҷ�ͼ��

extern ball MainBall;

/*============================================
·�����ƽṹ��
==========================================*/
//ö�ٶ��嵱ǰ��ѡ��Ĺ���
typedef enum
{
  BasicFunction1, //��������1
  BasicFunction2,
  BasicFunction3,
  BasicFunction4,
  AdvanceFunction1,
  AdvanceFunction2,
  AdvanceFunction3,
  
  UserControl,  //�Լ��趨·��,��������,���������ѡ���
  
  MAXFunction
}function;

//ö�ٶ���ĵ�·����,�����ƹ��ϰ���
typedef enum 
{
  BasicType,    //��ͨ����,������
  BiagonalType, //�Խ�������
  GapWType,
  GapWFType,
  GapHType,
  GapHFType,
  
  MAXType
}RoadType;

//����·���ṹ��,����9+8��λ��,����õ�·��,�û��������·����
typedef struct
{
  position AimPosition[20];   //����9+8�����λ��
  char Function;              //���浱ǰ��ѡ��Ĺ���
  position StoredPath[8][40]; //���治ͬ���ܵ�·��
  unsigned char CurrentPositionCounter;
  unsigned char TransPointFlag; //��־λ,�ж��Ƿ����м�ת�Ƶ���
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


//PID�ṹ��,ע���޸Ĳ������޸�PSet,�޸�P����Ч��
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
//ö�ٶ��������
typedef enum
{
  W,
  H,
  MAX
}servo_enum;

#define MAX_POSITION_W  1080    //�����������Сֵ
#define MAX_POSITION_H  1080
#define MIN_POSITION_W  300
#define MIN_POSITION_H  300

#define Servo_FTM FTM2          //�������ܽ�
#define Servo_W_FTM FTM_CH1
#define Servo_H_FTM FTM_CH0
#define Serv0_HZ    50


//���������ͽṹ����ƶ��
typedef struct
{
  pidbase PidBase;  //pid��������PID����
  int OutPosition;  //�������������ϵ�PWMֵ
  int Middle;       //�����ֵ
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