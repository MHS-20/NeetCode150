#include <stdlib.h>
#include <string.h>

static void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void backtrack(int *cur, int n, int idx, int **result, int *returnSize) {
  if (idx == n) {
    result[*returnSize] = malloc(n * sizeof(int));
    memcpy(result[(*returnSize)++], cur, n * sizeof(int));
    return;
  }

  for (int i = idx; i < n; i++) {
    swap(&cur[idx], &cur[i]);
    backtrack(cur, n, idx + 1, result, returnSize);
    swap(&cur[idx], &cur[i]);
  }
}

int **permute(int *nums, int numsSize, int *returnSize,
              int **returnColumnSizes) {
  int total = 1;
  for (int i = 2; i <= numsSize; i++)
    total *= i;

  int **result = malloc(total * sizeof(int *));
  *returnColumnSizes = malloc(total * sizeof(int));
  for (int i = 0; i < total; i++)
    (*returnColumnSizes)[i] = numsSize;
  *returnSize = 0;

  int *cur = malloc(numsSize * sizeof(int));
  memcpy(cur, nums, numsSize * sizeof(int));
  backtrack(cur, numsSize, 0, result, returnSize);
  free(cur);
  return result;
}
