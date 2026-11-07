#include <cstdlib>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
  int tot, target;
  vector<vector<int>> dp; // dp[i][sum + tot], -1 = not computed

  // Ways to reach target using nums[i..], given the running sum so far
  int f(int i, int sum, vector<int> &nums) {
    if (i == (int)nums.size())
      return sum == target ? 1 : 0;
    if (dp[i][sum + tot] != -1)
      return dp[i][sum + tot];

    int add = f(i + 1, sum + nums[i], nums); // +nums[i]
    int sub = f(i + 1, sum - nums[i], nums); // -nums[i]
    return dp[i][sum + tot] = add + sub;
  }

public:
  int findTargetSumWays(vector<int> &nums, int target) {
    int n = nums.size();
    tot = accumulate(nums.begin(), nums.end(), 0);
    if (abs(target) > tot)
      return 0;

    this->target = target;
    dp.assign(n, vector<int>(2 * tot + 1, -1));
    return f(0, 0, nums);
  }
};
