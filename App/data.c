#include "data.h"
#include "include.h"

uint8 imgbuff[CAMERA_SIZE];   
uint8 img[CAMERA_H][CAMERA_W];
position CurrentAimPosition;
char BlueToothReceiveAera[20];
position AimPosition[9];
position path[9];
ball MainBall;
int CurrentPath;//当前位置
char sendflag;
servo ServoBase[2];             //舵机控制结构体