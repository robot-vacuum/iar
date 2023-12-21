#ifndef __MAP_H__
#define __MAP_H__

#define MAP_SIZE 100

#define X_MAX 1000.0
#define Y_MAX 1000.0

#define THRESHOLD 1.0  // float로 정의된 Point 간 비교를 위한 임계값
#define CCW_THRESHOLD 0.5  // CCW 계산을 위한 임계값

struct Point {
  float x;
  float y;
} typedef Point;

extern Point source_Map[MAP_SIZE];
extern int source_Map_size;
extern int source_Map_Idx;

extern Point target_Map[MAP_SIZE];
extern int target_Map_size;
extern int target_Map_Idx;

extern void initMap(Point *map, int *map_size, int *map_Idx);

extern int getCCW(Point p1, Point p2, Point p3);

extern float getDistance(Point p1, Point p2);

extern void sortMap(Point *map, const int *map_size);

extern void sortMapByX(Point *map, const int *map_size);

extern void sortMapByCCW(Point *map, const int *map_size);

extern void assignConvexHull(Point *map, int *map_size);

extern void calcAndStoreMidPoints(Point *map_Source, Point *map_Target,
                                  const int *map_SourceSize,
                                  int *map_TargetSize);

#endif //MAP_H
