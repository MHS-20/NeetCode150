#include <stdlib.h>

static int *copyInterval(int start, int end) {
  int *p = malloc(2 * sizeof(int));
  p[0] = start;
  p[1] = end;
  return p;
}

int **insert(int **intervals, int intervalsSize, int *intervalsColSize,
             int *newInterval, int newIntervalSize, int *returnSize,
             int **returnColumnSizes) {
  (void)intervalsColSize;
  (void)newIntervalSize;
  int **result = malloc((intervalsSize + 1) * sizeof(int *));
  int n = 0, i = 0;
  int start = newInterval[0], end = newInterval[1];

  // 1. Intervals entirely before newInterval
  while (i < intervalsSize && intervals[i][1] < start) {
    result[n++] = copyInterval(intervals[i][0], intervals[i][1]);
    i++;
  }

  // 2. Intervals overlapping newInterval: absorb them into it
  while (i < intervalsSize && intervals[i][0] <= end) {
    if (intervals[i][0] < start)
      start = intervals[i][0];
    if (intervals[i][1] > end)
      end = intervals[i][1];
    i++;
  }
  result[n++] = copyInterval(start, end);

  // 3. Intervals entirely after newInterval
  while (i < intervalsSize) {
    result[n++] = copyInterval(intervals[i][0], intervals[i][1]);
    i++;
  }

  *returnSize = n;
  *returnColumnSizes = malloc(n * sizeof(int));
  for (int j = 0; j < n; j++)
    (*returnColumnSizes)[j] = 2;
  return result;
}
