#ifndef POSITIONCONTROL_H
#define POSITIONCONTROL_H

extern void AimPositionInit();
extern void PathInit();
//extern void AtPosition(position base);��data.h,�������д����
//extern bool AtPositionNonBlocking(position base);
extern void CalculatePosition();
extern void SetAimPosition();
//extern void SetPID(Servo* Base);


#endif //POSITIONCONTROL_H