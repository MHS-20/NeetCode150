#include <stdlib.h>

/**
 * Definition of Interval:
 * typedef struct {
 *     int start, end;
 * } Interval;
 */

static int cmpStart(const void *a, const void *b) {
  const Interval *x = a, *y = b;
  return (x->start > y->start) - (x->start < y->start);
}

static void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void push(int *heap, int *size, int x) {
  int i = (*size)++;
  heap[i] = x;
  while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
    swap(&heap[(i - 1) / 2], &heap[i]);
    i = (i - 1) / 2;
  }
}

static void pop(int *heap, int *size) {
  heap[0] = heap[--(*size)];
  int i = 0;
  for (;;) {
    int s = i, l = 2 * i + 1, r = l + 1;
    if (l < *size && heap[l] < heap[s])
      s = l;
    if (r < *size && heap[r] < heap[s])
      s = r;
    if (s == i)
      break;
    swap(&heap[s], &heap[i]);
    i = s;
  }
}

int minMeetingRooms(Interval *intervals, int intervalsSize) {
  int mx = 0, size = 0;
  int *minHeap = malloc((intervalsSize + 1) * sizeof(int)); // end times

  qsort(intervals, intervalsSize, sizeof(Interval), cmpStart);

  for (int i = 0; i < intervalsSize; i++) {
    while (size > 0 && minHeap[0] <= intervals[i].start)
      pop(minHeap, &size);
    push(minHeap, &size, intervals[i].end);
    if (size > mx)
      mx = size;
  }

  free(minHeap);
  return mx;
}
