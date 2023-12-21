#include "move.h"
#include <math.h>

int chkIsInCourse(const int *map_size, Point *current_Loc)
{
    int size = *map_size;

    for (int i = 0; i < size; i++) {
        if (getCCW(target_Map[i], target_Map[(i + 1) % size], *current_Loc) < 0) {
            return 0;
        }
    }

    return 1;
}

float getTheta(Point p0, Point p1, Point p2)
{
    Point v0 = {p1.x - p0.x, p1.y - p0.y}, v1 = {p2.x - p0.x, p2.y - p0.y};

    float dot = v0.x * v1.x + v0.y * v1.y;
    float det = getDistance(p0, p1) * getDistance(p0, p2);

    return acosf(dot / det) * (float)getCCW(p0, p1, p2);
}

int chkArrived(Point p0, Point p1)
{
    return getDistance(p0, p1) < THRESHOLD;
}

void moveForwardToNextPoint(Point *next_Point)
{
    Point current_Point = target_Map[target_Map_Idx], before_Point = source_Map_Idx == 0 ? target_Map[0] : source_Map[source_Map_Idx - 1];

    float thetaWithBefore = getTheta(before_Point, current_Point, *next_Point);

    if (thetaWithBefore != 0) {
        // Hardware-Level Control
        motorRotate(thetaWithBefore);
    }

    while(chkArrived(current_Point, *next_Point) == 0 && getCCW(*next_Point, (Point){next_Point->x + 1, next_Point->y}, current_Point) >= 0) {
        // Can be interrupted by sensors
        float thetaWithX = getTheta(current_Point, (Point){current_Point.x + 1, current_Point.y}, *next_Point);

        // Hardware-Level Control
        motorForwardOneTick();

        current_Point.x += FORWARD_TICK * cosf(thetaWithX);
        current_Point.y += FORWARD_TICK * sinf(thetaWithX);
    }

    if (chkArrived(current_Point, *next_Point) != 0) {
        source_Map[source_Map_Idx] = current_Point;
        source_Map_Idx++;
        moveForwardToNextPoint(next_Point);
    }
}