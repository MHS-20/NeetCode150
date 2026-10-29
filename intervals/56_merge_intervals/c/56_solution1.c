#include <stdlib.h>

static int cmpIntervals(const void *a, const void *b) {
  const int *x = *(int *const *)a, *y = *(int *const *)b;
  if (x[0] != y[0])
    return x[0] < y[0] ? -1 : 1;
  return x[1] < y[1] ? -1 : x[1] > y[1];
}

int **merge(int **intervals, int intervalsSize, int *intervalsColSize,
            int *returnSize, int **returnColumnSizes) {
  (void)intervalsColSize;
  qsort(intervals, intervalsSize, sizeof(int *), cmpIntervals);

  int **result = malloc(intervalsSize * sizeof(int *));
  int n = 0;

  for (int i = 0; i < intervalsSize; i++) {
    if (n == 0 || result[n - 1][1] < intervals[i][0]) {
      result[n] = malloc(2 * sizeof(int));
      result[n][0] = intervals[i][0];
      result[n][1] = intervals[i][1];
      n++;
    } else if (intervals[i][1] > result[n - 1][1]) {
      result[n - 1][1] = intervals[i][1];
    }
  }

  *returnSize = n;
  *returnColumnSizes = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    (*returnColumnSizes)[i] = 2;
  return result;
}
