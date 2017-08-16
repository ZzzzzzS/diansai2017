#include "data.h"
#include "include.h"

uint8 imgbuff[CAMERA_SIZE];   
uint8 img[CAMERA_H][CAMERA_W];
uint8 imgFixed[CAMERA_H][CAMERA_W];
char BlueToothReceiveAera[20];
ball MainBall;
servo ServoBase[2];
path PathBase;
char sendflag;
volatile char KeyState;
volatile char RemoteKeyState;