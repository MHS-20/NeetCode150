#include <stdlib.h>
#include <string.h>

typedef struct {
  int **rows;
  int *colSizes;
  int size;
  int cap;
} Result;

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

static void backtrack(Result *res, int *cur, int curSize, int idx,
                      const int *candidates, int n, int target, int sum) {
  if (sum == target) {
    save(res, cur, curSize);
    return;
  }
  if (sum > target || idx >= n)
    return;

  // include candidates[idx], stay on idx (can reuse it)
  cur[curSize] = candidates[idx];
  backtrack(res, cur, curSize + 1, idx, candidates, n, target,
            sum + candidates[idx]);

  // skip candidates[idx] for good, move on
  backtrack(res, cur, curSize, idx + 1, candidates, n, target, sum);
}

int **combinationSum(int *candidates, int candidatesSize, int target,
                     int *returnSize, int **returnColumnSizes) {
  Result res = {0};
  int *cur = malloc(target * sizeof(int)); // candidates >= 1, so depth <= target
  backtrack(&res, cur, 0, 0, candidates, candidatesSize, target, 0);
  free(cur);
  *returnSize = res.size;
  *returnColumnSizes = res.colSizes;
  return res.rows;
}
