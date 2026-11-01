#include <stdlib.h>

typedef struct {
  int size, end; // heap ordered by size, then end
} Entry;

static int **sortedIntervals;
static int *sortedQueries;

static int cmpInterval(const void *a, const void *b) {
  const int *x = *(int *const *)a, *y = *(int *const *)b;
  return (x[0] > y[0]) - (x[0] < y[0]);
}

static int cmpQueryIdx(const void *a, const void *b) {
  int x = sortedQueries[*(const int *)a], y = sortedQueries[*(const int *)b];
  return (x > y) - (x < y);
}

static int less(Entry a, Entry b) {
  return a.size < b.size || (a.size == b.size && a.end < b.end);
}

static void push(Entry *heap, int *len, Entry e) {
  int i = (*len)++;
  while (i > 0 && less(e, heap[(i - 1) / 2])) {
    heap[i] = heap[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  heap[i] = e;
}

static void pop(Entry *heap, int *len) {
  Entry last = heap[--(*len)];
  int i = 0;
  for (;;) {
    int child = 2 * i + 1;
    if (child >= *len)
      break;
    if (child + 1 < *len && less(heap[child + 1], heap[child]))
      child++;
    if (!less(heap[child], last))
      break;
    heap[i] = heap[child];
    i = child;
  }
  heap[i] = last;
}

int *minInterval(int **intervals, int intervalsSize, int *intervalsColSize,
                 int *queries, int queriesSize, int *returnSize) {
  (void)intervalsColSize; // always 2
  sortedIntervals = intervals;
  sortedQueries = queries;

  int *result = malloc(queriesSize * sizeof(int));
  int *idx = malloc(queriesSize * sizeof(int));
  Entry *heap = malloc((intervalsSize ? intervalsSize : 1) * sizeof(Entry));
  int len = 0;

  qsort(intervals, intervalsSize, sizeof(int *), cmpInterval);
  for (int k = 0; k < queriesSize; k++)
    idx[k] = k;
  qsort(idx, queriesSize, sizeof(int), cmpQueryIdx);

  int i = 0;
  for (int k = 0; k < queriesSize; k++) {
    int j = idx[k], q = queries[j];

    while (i < intervalsSize && intervals[i][0] <= q) {
      Entry e = {intervals[i][1] - intervals[i][0] + 1, intervals[i][1]};
      push(heap, &len, e);
      i++;
    }

    while (len > 0 && heap[0].end < q)
      pop(heap, &len);

    result[j] = len == 0 ? -1 : heap[0].size;
  }

  free(idx);
  free(heap);
  *returnSize = queriesSize;
  return result;
}
