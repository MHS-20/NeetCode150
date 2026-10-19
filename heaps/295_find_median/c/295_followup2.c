#include <stdlib.h>

typedef struct {
  int cnt[101];
  int below; // numbers < 0
  int above; // numbers > 100
  int total;
} MedianFinder;

static int kth(const MedianFinder *obj, int k) {
  int seen = obj->below; // outliers below the range come first in sorted order
  for (int v = 0; v <= 100; v++) {
    seen += obj->cnt[v];
    if (seen >= k)
      return v;
  }
  return -1;
}

MedianFinder *medianFinderCreate() { return calloc(1, sizeof(MedianFinder)); }

void medianFinderAddNum(MedianFinder *obj, int num) {
  if (num < 0)
    obj->below++;
  else if (num > 100)
    obj->above++;
  else
    obj->cnt[num]++;
  obj->total++;
}

double medianFinderFindMedian(MedianFinder *obj) {
  int a = kth(obj, (obj->total + 1) / 2);
  int b = kth(obj, obj->total / 2 + 1);
  return (a + b) / 2.0;
}

void medianFinderFree(MedianFinder *obj) { free(obj); }
