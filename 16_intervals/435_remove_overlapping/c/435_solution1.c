#include <stdlib.h>

static int cmpIntervals(const void *a, const void *b) {
  const int *x = *(int *const *)a, *y = *(int *const *)b;
  if (x[0] != y[0])
    return x[0] < y[0] ? -1 : 1;
  return x[1] < y[1] ? -1 : x[1] > y[1];
}

int eraseOverlapIntervals(int **intervals, int intervalsSize,
                          int *intervalsColSize) {
  (void)intervalsColSize;
  qsort(intervals, intervalsSize, sizeof(int *), cmpIntervals);
  int kept = 0;
  int lastEnd = 0; // end of the last kept interval

  for (int i = 0; i < intervalsSize; i++) {
    if (kept == 0 || lastEnd <= intervals[i][0]) {
      kept++;
      lastEnd = intervals[i][1];
    } else if (lastEnd > intervals[i][1]) {
      lastEnd = intervals[i][1]; // overlap: keep the one that ends earlier
    }
  }

  return intervalsSize - kept;
}
