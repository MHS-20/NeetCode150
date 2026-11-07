#include <stdlib.h>

static int min(int a, int b) { return a < b ? a : b; }

static int costs(int i, int *cost, int *memo) {
  if (i <= 1)
    return 0; // start on step 0 or 1 for free
  if (memo[i] != -1)
    return memo[i];
  return memo[i] = min(costs(i - 1, cost, memo) + cost[i - 1],
                       costs(i - 2, cost, memo) + cost[i - 2]);
}

int minCostClimbingStairs(int *cost, int costSize) {
  int *memo = malloc((costSize + 1) * sizeof(int));
  for (int i = 0; i <= costSize; i++)
    memo[i] = -1;
  int res = costs(costSize, cost, memo);
  free(memo);
  return res;
}
