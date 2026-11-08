#include <stdlib.h>

#define MAXC 1001 // coordinates are in [0, 1000]

typedef struct {
  int cnt[MAXC][MAXC];
  int (*pts)[2]; // distinct points, so count() walks only those
  int len, cap;
} DetectSquares;

DetectSquares *detectSquaresCreate() {
  DetectSquares *obj = calloc(1, sizeof(DetectSquares));
  obj->cap = 16;
  obj->pts = malloc(sizeof(int[2]) * obj->cap);
  return obj;
}

void detectSquaresAdd(DetectSquares *obj, int *point, int pointSize) {
  int x = point[0], y = point[1];
  if (obj->cnt[x][y]++ > 0)
    return;
  if (obj->len == obj->cap) {
    obj->cap *= 2;
    obj->pts = realloc(obj->pts, sizeof(int[2]) * obj->cap);
  }
  obj->pts[obj->len][0] = x;
  obj->pts[obj->len][1] = y;
  obj->len++;
}

int detectSquaresCount(DetectSquares *obj, int *point, int pointSize) {
  int x = point[0], y = point[1], res = 0;

  for (int i = 0; i < obj->len; i++) {
    int px = obj->pts[i][0], py = obj->pts[i][1];
    if (px == x || abs(px - x) != abs(py - y))
      continue; // must be a diagonal corner with side length > 0
    res += obj->cnt[px][py] * obj->cnt[x][py] * obj->cnt[px][y];
  }
  return res;
}

void detectSquaresFree(DetectSquares *obj) {
  free(obj->pts);
  free(obj);
}
