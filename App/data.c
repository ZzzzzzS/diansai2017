#include "data.h"
#include "include.h"

uint8 imgbuff[CAMERA_SIZE];   
uint8 img[CAMERA_H][CAMERA_W];
position CurrentAimPosition;
char BlueToothReceiveAera[20];
position AimPosition[9];
position path[9];
ball MainBall;
int CurrentPath;//��ǰλ��
char sendflag;
servo ServoBase[2];             //������ƽṹ��