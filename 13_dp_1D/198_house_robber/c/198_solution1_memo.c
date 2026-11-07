#include <stdlib.h>

static int max(int a, int b) { return a > b ? a : b; }

static int maxLoot(int idx, int *nums, int *memo) {
  if (idx == 0)
    return nums[0];
  if (idx == 1)
    return max(nums[0], nums[1]);

  if (memo[idx] != -1)
    return memo[idx];

  return memo[idx] =
             max(maxLoot(idx - 1, nums, memo),              // skip this house
                 maxLoot(idx - 2, nums, memo) + nums[idx]); // rob this house
}

int rob(int *nums, int numsSize) {
  int *memo = malloc(numsSize * sizeof(int));
  for (int i = 0; i < numsSize; i++)
    memo[i] = -1;
  int res = maxLoot(numsSize - 1, nums, memo);
  free(memo);
  return res;
}
