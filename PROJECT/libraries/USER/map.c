#include "map.h"

#include <math.h>

Point source_Map[MAP_SIZE]; // 출발지 맵
int source_Map_size; // 출발지 맵 크기
int source_Map_Idx = 0; // 출발지 맵 index

Point target_Map[MAP_SIZE]; // 목적지 맵
int target_Map_size; // 목적지 맵 크기
int target_Map_Idx = 0; // 목적지 맵 index

const Point init_map[4] = {{0, 0}, {X_MAX, 0}, {X_MAX, Y_MAX}, {0, Y_MAX}}; // 초기 맵 정보

static Point stack[MAP_SIZE]; // Convex Hull을 위한 stack
static int stack_top = 0;


// 세 점이 이루는 CCW 값 계산하는 함수
int getCCW(Point p1, Point p2, Point p3) {
  float temp = p1.x * p2.y - p1.y * p2.x;
  temp += p2.x * p3.y - p2.y * p3.x;
  temp += p3.x * p1.y - p3.y * p1.x;

  if (temp > CCW_THRESHOLD)
    return 1;
  else if (temp < CCW_THRESHOLD)
    return -1;

  return 0;
}

// 두 점 사이의 거리 계산하는 함수
float getDistance(Point p1, Point p2) { return sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)); }

// 맵 초기화 함수
void initMap(Point *map, int *map_size, int *map_Idx) {
  int size = *map_size = 4;

  for (*map_Idx = -1; *map_Idx - 1 < size; ) {
    (*map_Idx)++;
    map[*map_Idx] = init_map[*map_Idx];
  }
}

// 맵 정렬 함수
void sortMap(Point *map, const int *map_size) {
  int size = *map_size;

  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (map[i].x > map[j].x) {
        Point tmp = map[i];
        map[i] = map[j];
        map[j] = tmp;
      }
    }
  }
}

// 맵 x좌표 기준 정렬 함수
void sortMapByX(Point *map, const int *map_size) {
  int size = *map_size;

  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (map[i].x > map[j].x) {
        Point tmp = map[i];
        map[i] = map[j];
        map[j] = tmp;
      }
    }
  }
}

// 맵 CCW 기준 정렬 함수
void sortMapByCCW(Point *map, const int *map_size) {
  int size = *map_size;

  // except i == 0
  for (int i = 1; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (getCCW(map[0], map[i], map[j]) > 0) {
        Point tmp = map[i];
        map[i] = map[j];
        map[j] = tmp;
      }
    }
  }
}

// assign convex hull using by Graham's Scan Algorithm
void assignConvexHull(Point *map, int *map_size) {
  int size = *map_size;

  // sort map by x
  sortMapByX(map, map_size);
  // sort map by ccw
  sortMapByCCW(map, map_size);

  // assign convex hull
  stack[stack_top++] = map[0];
  stack[stack_top++] = map[1];
  for (int i = 2; i < size; i++) {
    while (stack_top >= 2 && getCCW(stack[stack_top - 2], stack[stack_top - 1], map[i]) <= 0) {
      stack_top--;
    }
    stack[stack_top++] = map[i];
  }

  // assign convex hull
  for (int i = 0; i < stack_top; i++) {
    map[i] = stack[i];
  }

  *map_size = stack_top;

  stack_top = 0;
}

// calculate and store mid points
void calcAndStoreMidPoints(Point *map_Source, Point *map_Target, const int *map_SourceSize, int *map_TargetSize) {
  int size = *map_SourceSize;
  int targetIndex = -1;

  for (int i = 0; i < size; i++) {
    Point midPoint;
    midPoint.x = (map_Source[(i - 1 + size) % size].x + map_Source[(i + 1) % size].x) / 2;
    midPoint.y = (map_Source[(i - 1 + size) % size].y + map_Source[(i + 1) % size].y) / 2;

    if (targetIndex == -1 || getDistance(midPoint, map_Target[targetIndex - 1]) > THRESHOLD) {
      map_Target[++targetIndex] = midPoint;
    }
  }

  target_Map_Idx = targetIndex;
  *map_TargetSize = targetIndex + 1;
}
