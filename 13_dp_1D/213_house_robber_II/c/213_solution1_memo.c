#include <stdlib.h>

static int max(int a, int b) { return a > b ? a : b; }

static int maxLoot(int idx, int start, int *nums, int *memo) {
  if (idx < start)
    return 0;
  if (memo[idx] != -1)
    return memo[idx];
  return memo[idx] = max(maxLoot(idx - 1, start, nums, memo),
                         maxLoot(idx - 2, start, nums, memo) + nums[idx]);
}

static void reset(int *memo, int n) {
  for (int i = 0; i < n; i++)
    memo[i] = -1;
}

int rob(int *nums, int numsSize) {
  int n = numsSize;
  if (n == 1)
    return nums[0];

  int *memo = malloc(n * sizeof(int));
  reset(memo, n);
  int skipLast = maxLoot(n - 2, 0, nums, memo);

  reset(memo, n); // reset: different subproblem
  int skipFirst = maxLoot(n - 1, 1, nums, memo);

  free(memo);
  return max(skipLast, skipFirst);
}
