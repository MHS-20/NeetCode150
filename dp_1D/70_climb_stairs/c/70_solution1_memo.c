#include <stdlib.h>

static int ways(int i, int *memo) {
  if (i <= 2)
    return i; // ways(1) = 1, ways(2) = 2
  if (memo[i] != -1)
    return memo[i];
  return memo[i] = ways(i - 1, memo) + ways(i - 2, memo);
}

int climbStairs(int n) {
  int *memo = malloc((n + 1) * sizeof(int));
  for (int i = 0; i <= n; i++)
    memo[i] = -1;
  int res = ways(n, memo);
  free(memo);
  return res;
}
