#include <stdlib.h>
#include <string.h>

typedef struct {
  int **rows;
  int *colSizes;
  int size;
  int cap;
} Result;

static int cmp(const void *a, const void *b) {
  int x = *(const int *)a, y = *(const int *)b;
  return (x > y) - (x < y);
}

static void save(Result *res, const int *cur, int curSize) {
  if (res->size == res->cap) {
    res->cap = res->cap ? 2 * res->cap : 16;
    res->rows = realloc(res->rows, res->cap * sizeof(int *));
    res->colSizes = realloc(res->colSizes, res->cap * sizeof(int));
  }
  res->rows[res->size] = malloc(curSize * sizeof(int));
  memcpy(res->rows[res->size], cur, curSize * sizeof(int));
  res->colSizes[res->size++] = curSize;
}

static void backtrack(const int *candidates, int n, int idx, int sum,
                      int target, int *cur, int curSize, Result *res) {
  if (sum == target) {
    save(res, cur, curSize);
    return;
  }

  if (sum > target || idx == n)
    return;

  cur[curSize] = candidates[idx];
  backtrack(candidates, n, idx + 1, sum + candidates[idx], target, cur,
            curSize + 1, res);

  int i = idx + 1;
  while (i < n && candidates[i] == candidates[idx])
    i++;
  backtrack(candidates, n, i, sum, target, cur, curSize, res);
}

int **combinationSum2(int *candidates, int candidatesSize, int target,
                      int *returnSize, int **returnColumnSizes) {
  Result res = {0};
  qsort(candidates, candidatesSize, sizeof(int), cmp);
  int *cur = malloc((candidatesSize ? candidatesSize : 1) * sizeof(int)); // each used at most once
  backtrack(candidates, candidatesSize, 0, 0, target, cur, 0, &res);
  free(cur);
  *returnSize = res.size;
  *returnColumnSizes = res.colSizes;
  return res.rows;
}
