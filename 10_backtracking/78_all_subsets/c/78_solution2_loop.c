#include <stdlib.h>
#include <string.h>

static void backtrack(int *nums, int n, int start, int *cur, int curSize,
                      int **result, int *returnSize, int *colSizes) {
  // every path is a valid subset
  result[*returnSize] = malloc(curSize * sizeof(int));
  memcpy(result[*returnSize], cur, curSize * sizeof(int));
  colSizes[(*returnSize)++] = curSize;

  for (int i = start; i < n; i++) {
    cur[curSize] = nums[i];
    backtrack(nums, n, i + 1, cur, curSize + 1, result, returnSize, colSizes);
  }
}

int **subsets(int *nums, int numsSize, int *returnSize,
              int **returnColumnSizes) {
  int total = 1 << numsSize;
  int **result = malloc(total * sizeof(int *));
  *returnColumnSizes = malloc(total * sizeof(int));
  *returnSize = 0;
  int cur[numsSize > 0 ? numsSize : 1];
  backtrack(nums, numsSize, 0, cur, 0, result, returnSize, *returnColumnSizes);
  return result;
}
