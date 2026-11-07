#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> memo;

  int maxLoot(int idx, vector<int> &nums) {
    if (idx == 0)
      return nums[0];
    if (idx == 1)
      return max(nums[0], nums[1]);

    if (memo[idx] != -1)
      return memo[idx];

    return memo[idx] =
               max(maxLoot(idx - 1, nums),              // skip this house
                   maxLoot(idx - 2, nums) + nums[idx]); // rob this house
  }

  int rob(vector<int> &nums) {
    memo.assign(nums.size(), -1);
    return maxLoot(nums.size() - 1, nums);
  }
};
