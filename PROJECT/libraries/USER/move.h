#ifndef __MOVE_H__
#define __MOVE_H__

#include "map.h"
#include "motor.h"
#include "configuration.h"

#define FORWARD_TICK 100.0
#define ROTATE_TICK 1.0

extern int global_Theta;
extern Point global_Current_Point, global_Next_Point;

extern int chkIsInCourse();

extern int chkArrived(Point p0, Point p1);

extern int getTheta(Point p0, Point p1, Point p2);

extern void moveForwardToNextPoint();

extern void generalMove();
#endif  // MOVE_H
