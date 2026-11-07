#include <algorithm>
#include <vector>

using namespace std;

class Solution {
  vector<int> memo;

  int costs(int i, vector<int> &cost) {
    if (i <= 1)
      return 0; // start on step 0 or 1 for free
    if (memo[i] != -1)
      return memo[i];
    return memo[i] = min(costs(i - 1, cost) + cost[i - 1],
                         costs(i - 2, cost) + cost[i - 2]);
  }

public:
  int minCostClimbingStairs(vector<int> &cost) {
    memo.assign(cost.size() + 1, -1);
    return costs(cost.size(), cost);
  }
};
