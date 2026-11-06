#include <algorithm>
#include <vector>

using namespace std;

class Solution {
  // Max loot from houses start..end (inclusive), in a straight line
  int robRange(vector<int> &nums, int start, int end) {
    int len = end - start + 1;
    if (len == 1)
      return nums[start];

    vector<int> dp(len);
    dp[0] = nums[start];
    dp[1] = max(nums[start], nums[start + 1]);

    for (int i = 2; i < len; i++) {
      dp[i] = max(dp[i - 1],                    // skip this house
                  dp[i - 2] + nums[start + i]); // rob this house
    }
    return dp[len - 1];
  }

public:
  int rob(vector<int> &nums) {
    int n = nums.size();
    if (n == 1)
      return nums[0];

    return max(robRange(nums, 0, n - 2),  // exclude the last house
               robRange(nums, 1, n - 1)); // exclude the first house
  }
};
