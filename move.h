#ifndef __MOVE_H
#define __MOVE_H

#include "map.h"

#define FORWARD_TICK 1.0
#define ROTATE_TICK 1.0

extern void motorForwardOneTick();
extern void motorRotate(float theta);

int chkIsInCourse(const int *map_size, Point *current_Loc);

int chkArrived(Point p0, Point p1);

float getTheta(Point p0, Point p1, Point p2);

void moveForwardToNextPoint(Point *next_Point);

#endif //MOVE_H
