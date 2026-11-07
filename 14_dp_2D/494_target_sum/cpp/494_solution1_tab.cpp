#include <cstdlib>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  int findTargetSumWays(vector<int> &nums, int target) {
    int n = nums.size();
    int tot = accumulate(nums.begin(), nums.end(), 0);
    if (abs(target) > tot)
      return 0;

    vector<vector<int>> dp(n + 1, vector<int>(2 * tot + 1, 0));
    dp[0][0 + tot] = 1; // 0 numbers used, sum 0

    for (int i = 1; i <= n; i++) {
      int x = nums[i - 1];
      for (int s = -tot; s <= tot; s++) {
        int ways = 0;
        if (s - x >= -tot)
          ways += dp[i - 1][s - x + tot]; // added x
        if (s + x <= tot)
          ways += dp[i - 1][s + x + tot]; // subtracted x
        dp[i][s + tot] = ways;
      }
    }
    return dp[n][target + tot];
  }
};
