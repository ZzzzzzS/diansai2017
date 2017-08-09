#ifndef POSITIONCONTROL_H
#define POSITIONCONTROL_H

extern void AimPositionInit();
extern void PathInit();
//extern void AtPosition(position base);在data.h,此问题有待解决
extern void CalculatePosition();
extern void SetAimPosition();
#endif //POSITIONCONTROL_H