#include <stdlib.h>
#include <string.h>

static int cmp(const void *a, const void *b) {
  int x = *(const int *)a, y = *(const int *)b;
  return (x > y) - (x < y);
}

static void backtrack(int *nums, int n, int idx, int *cur, int curSize,
                      int **result, int *returnSize, int *colSizes) {
  if (idx == n) {
    result[*returnSize] = malloc(curSize * sizeof(int));
    memcpy(result[*returnSize], cur, curSize * sizeof(int));
    colSizes[(*returnSize)++] = curSize;
    return;
  }

  cur[curSize] = nums[idx];
  backtrack(nums, n, idx + 1, cur, curSize + 1, result, returnSize, colSizes);

  int i = idx + 1;
  while (i < n && nums[idx] == nums[i])
    i++;

  backtrack(nums, n, i, cur, curSize, result, returnSize, colSizes);
}

int **subsetsWithDup(int *nums, int numsSize, int *returnSize,
                     int **returnColumnSizes) {
  int total = 1 << numsSize; // upper bound, reached only without duplicates
  int **result = malloc(total * sizeof(int *));
  *returnColumnSizes = malloc(total * sizeof(int));
  *returnSize = 0;
  qsort(nums, numsSize, sizeof(int), cmp);
  int cur[numsSize > 0 ? numsSize : 1];
  backtrack(nums, numsSize, 0, cur, 0, result, returnSize, *returnColumnSizes);
  return result;
}
