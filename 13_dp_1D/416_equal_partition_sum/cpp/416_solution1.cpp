#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  bool canPartition(vector<int> &nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2 != 0)
      return false;
    int target = total / 2;

    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int x : nums) {
      // Go backward so each number is used at most once
      for (int s = target; s >= x; s--) {
        if (dp[s - x])
          dp[s] = true;
      }
    }
    return dp[target];
  }
};
