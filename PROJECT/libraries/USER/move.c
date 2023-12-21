#include "move.h"
#include <math.h>

int global_Theta = 0;
Point global_Current_Point, global_Next_Point;

float thetaToRad(int theta) { return (float)theta * M_PI / 180; }

int chkIsInCourse() {
  int size = target_Map_size;

  for (int i = 0; i < size; i++) {
    if (getCCW(target_Map[i], target_Map[(i + 1) % size],
               global_Current_Point) == 0) {
      return (i + 1) % size + 1;
    }
  }

  return 0;
}

int getTheta(Point p0, Point p1, Point p2) {
  Point v0 = {p1.x - p0.x, p1.y - p0.y}, v1 = {p2.x - p0.x, p2.y - p0.y};

  float dot = v0.x * v1.x + v0.y * v1.y;
  float det = getDistance(p0, p1) * getDistance(p0, p2);

  return (int)((acosf(dot / det) * (float)getCCW(p0, p1, p2) * 180 / M_PI) +
               360) %
         360;
}

int chkArrived(Point p0, Point p1) { return getDistance(p0, p1) < THRESHOLD; }

void moveForwardToNextPoint() {
  Point unit_Vector;

  while (chkArrived(global_Current_Point, global_Next_Point) == 0 &&
         getCCW(global_Next_Point,
                (Point){global_Next_Point.x + 1, global_Next_Point.y},
                global_Current_Point) >= 0) {
    unit_Vector.x = global_Current_Point.x + 1;
    unit_Vector.y = global_Current_Point.y;

    while (getTheta(global_Current_Point, unit_Vector, global_Next_Point) !=
               global_Theta &&
           !isInturrupted)
      CLOCKWISE_ROTATION();

    if (isInturrupted) {
      return;
    }

    // Hardware-Level Control
    ONE_TICK_FORWARD();
  }
}

void moveForwardOnRightWall() {
  while (!chkIsInCourse() && GPIO_ReadInputDataBit(GPIO_Prox_Right_Port2,
                                                   GPIO_Prox_Right_Pin2) == 0) {
    ONE_TICK_FORWARD();
  }

  if (chkIsInCourse()) {
    global_Next_Point = target_Map[chkIsInCourse() - 1];
  } else {
    while (GPIO_ReadInputDataBit(GPIO_Prox_Right_Port1, GPIO_Prox_Right_Pin1) ==
           1) {
      ONE_TICK_CLOCKWISE_ROTATION();
    }

    moveForwardOnRightWall();
  }
}

void generalMove() {
    global_Next_Point = target_Map[0];
    moveForwardToNextPoint();

  for (target_Map_Idx = 1; target_Map_Idx < target_Map_size;) {
    if (!isInturrupted && chkIsInCourse()) {
      moveForwardToNextPoint();
    } else {
      isInturrupted = 0;
      moveForwardToNextPoint();
    }
  }
}
