#include <stdlib.h>
#include <string.h>

static void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void backtrack(int *nums, int n, int idx, int i, int **result,
                      int *returnSize) {
  if (idx == n) {
    result[*returnSize] = malloc(n * sizeof(int));
    memcpy(result[(*returnSize)++], nums, n * sizeof(int));
    return;
  }
  if (i == n)
    return;

  // choose nums[i] for position idx, then fix the next position
  swap(&nums[idx], &nums[i]);
  backtrack(nums, n, idx + 1, idx + 1, result, returnSize);
  swap(&nums[idx], &nums[i]); // undo

  // try the next candidate for the same position
  backtrack(nums, n, idx, i + 1, result, returnSize);
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

  backtrack(nums, numsSize, 0, 0, result, returnSize);
  return result;
}
