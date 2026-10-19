#include <stdlib.h>

typedef struct {
  int cnt[101];
  int total;
} MedianFinder;

static int kth(const MedianFinder *obj, int k) { // k-th smallest, 1-indexed
  int seen = 0;
  for (int v = 0; v <= 100; v++) {
    seen += obj->cnt[v];
    if (seen >= k)
      return v;
  }
  return -1; // unreachable if 1 <= k <= total
}

MedianFinder *medianFinderCreate() { return calloc(1, sizeof(MedianFinder)); }

void medianFinderAddNum(MedianFinder *obj, int num) {
  obj->cnt[num]++;
  obj->total++;
}

double medianFinderFindMedian(MedianFinder *obj) {
  int a = kth(obj, (obj->total + 1) / 2);
  int b = kth(obj, obj->total / 2 + 1);
  return (a + b) / 2.0;
}

void medianFinderFree(MedianFinder *obj) { free(obj); }
