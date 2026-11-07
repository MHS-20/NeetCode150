#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int minCostClimbingStairs(vector<int> &cost) {
    int n = cost.size();
    vector<int> dp(n + 1);
    dp[0] = 0; // start on step 0 for free
    dp[1] = 0; // start on step 1 for free

    for (int i = 2; i <= n; i++) {
      dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }
    return dp[n]; // n = the top, one past the last step
  }
};
