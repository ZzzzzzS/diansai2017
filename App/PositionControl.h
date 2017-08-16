#ifndef POSITIONCONTROL_H
#define POSITIONCONTROL_H

extern void AimPositionInit();
extern void PathInit();
//extern void AtPosition(position base);在data.h,此问题有待解决
//extern bool AtPositionNonBlocking(position base);
extern void CalculatePosition();
extern void SetAimPosition();
//extern void SetPID(Servo* Base);


#endif //POSITIONCONTROL_H