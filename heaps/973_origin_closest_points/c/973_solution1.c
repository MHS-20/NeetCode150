#include <stdlib.h>

typedef struct {
  int dist; // squared distance, same order as the real one
  int *point;
} Entry;

static void swap(Entry *a, Entry *b) {
  Entry t = *a;
  *a = *b;
  *b = t;
}

static void siftUp(Entry *h, int i) {
  while (i > 0 && h[(i - 1) / 2].dist < h[i].dist) {
    swap(&h[(i - 1) / 2], &h[i]);
    i = (i - 1) / 2;
  }
}

static void siftDown(Entry *h, int n, int i) {
  for (;;) {
    int max = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && h[l].dist > h[max].dist)
      max = l;
    if (r < n && h[r].dist > h[max].dist)
      max = r;
    if (max == i)
      return;
    swap(&h[max], &h[i]);
    i = max;
  }
}

int **kClosest(int **points, int pointsSize, int *pointsColSize, int k,
               int *returnSize, int **returnColumnSizes) {
  Entry *pq = malloc((k + 1) * sizeof(Entry)); // max-heap
  int n = 0;

  for (int i = 0; i < pointsSize; i++) {
    int *p = points[i];
    pq[n] = (Entry){p[0] * p[0] + p[1] * p[1], p};
    siftUp(pq, n++);
    if (n > k) {
      pq[0] = pq[--n];
      siftDown(pq, n, 0);
    }
  }

  int **res = malloc(n * sizeof(int *));
  *returnColumnSizes = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    res[i] = malloc(2 * sizeof(int));
    res[i][0] = pq[i].point[0];
    res[i][1] = pq[i].point[1];
    (*returnColumnSizes)[i] = 2;
  }
  *returnSize = n;

  free(pq);
  return res;
}
