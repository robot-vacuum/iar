#ifndef MAP_H
#define MAP_H

#define MAP_SIZE 100

#define X_MAX 100.0
#define Y_MAX 100.0

#define THRESHOLD 0.1 // float로 정의된 Point 간 비교를 위한 임계값

struct Point {
    float x;
    float y;
} typedef Point;

Point source_Map[MAP_SIZE];
int source_Map_size;
int source_Map_Idx = 0;

Point target_Map[MAP_SIZE];
int target_Map_size;
int target_Map_Idx = 0;


int getCCW(Point p1, Point p2, Point p3);

float getDistance(Point p1, Point p2);

void initMap(Point *map, int *map_size, int *map_Idx);

void sortMap(Point *map, const int *map_size);

void sortMapByX(Point *map, const int *map_size);

void sortMapByCCW(Point *map, const int *map_size);

void assignConvexHull(Point *map, int *map_size);

void calcAndStoreMidPoints(Point *map_Source, Point *map_Target, const int *map_SourceSize, int *map_TargetSize);

#endif //MAP_H
