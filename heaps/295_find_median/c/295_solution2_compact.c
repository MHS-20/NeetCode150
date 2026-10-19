#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int *data;
  int size;
  int cap;
  bool isMax;
} Heap;

// true if a must sit above b
static bool before(const Heap *h, int a, int b) {
  return h->isMax ? a > b : a < b;
}

static void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void push(Heap *h, int val) {
  if (h->size == h->cap) {
    h->cap = h->cap ? 2 * h->cap : 16;
    h->data = realloc(h->data, h->cap * sizeof(int));
  }
  int *d = h->data, i = h->size++;
  d[i] = val;
  while (i > 0 && before(h, d[i], d[(i - 1) / 2])) {
    swap(&d[i], &d[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

static int pop(Heap *h) {
  int *d = h->data, top = d[0], i = 0;
  d[0] = d[--h->size];
  for (;;) {
    int best = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < h->size && before(h, d[l], d[best]))
      best = l;
    if (r < h->size && before(h, d[r], d[best]))
      best = r;
    if (best == i)
      return top;
    swap(&d[best], &d[i]);
    i = best;
  }
}

typedef struct {
  Heap lo; // max-heap, lower half
  Heap hi; // min-heap, upper half
} MedianFinder;

MedianFinder *medianFinderCreate() {
  MedianFinder *obj = calloc(1, sizeof(MedianFinder));
  obj->lo.isMax = true;
  return obj;
}

void medianFinderAddNum(MedianFinder *obj, int num) {
  push(&obj->lo, num);
  push(&obj->hi, pop(&obj->lo));
  if (obj->hi.size > obj->lo.size)
    push(&obj->lo, pop(&obj->hi));
}

double medianFinderFindMedian(MedianFinder *obj) {
  if (obj->lo.size > obj->hi.size)
    return obj->lo.data[0];
  return (obj->lo.data[0] + obj->hi.data[0]) / 2.0;
}

void medianFinderFree(MedianFinder *obj) {
  free(obj->lo.data);
  free(obj->hi.data);
  free(obj);
}
