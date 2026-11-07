#include <stdlib.h>

int *productExceptSelf(int *nums, int numsSize, int *returnSize) {
  int *prefixes = (int *)malloc(numsSize * sizeof(int));
  int *suffixes = (int *)malloc(numsSize * sizeof(int));
  int *ans = (int *)malloc(numsSize * sizeof(int));

  prefixes[0] = 1;
  for (int i = 1; i < numsSize; i++)
    prefixes[i] = prefixes[i - 1] * nums[i - 1];

  suffixes[numsSize - 1] = 1;
  for (int i = numsSize - 2; i >= 0; i--)
    suffixes[i] = suffixes[i + 1] * nums[i + 1];

  for (int i = 0; i < numsSize; i++)
    ans[i] = prefixes[i] * suffixes[i];

  free(prefixes);
  free(suffixes);

  *returnSize = numsSize;
  return ans;
}
