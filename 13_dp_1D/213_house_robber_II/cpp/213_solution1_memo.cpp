#include <algorithm>
#include <vector>

using namespace std;

class Solution {
  vector<int> memo;

  int maxLoot(int idx, int start, vector<int> &nums) {
    if (idx < start)
      return 0;
    if (memo[idx] != -1)
      return memo[idx];
    return memo[idx] = max(maxLoot(idx - 1, start, nums),
                           maxLoot(idx - 2, start, nums) + nums[idx]);
  }

public:
  int rob(vector<int> &nums) {
    int n = nums.size();
    if (n == 1)
      return nums[0];

    memo.assign(n, -1);
    int skipLast = maxLoot(n - 2, 0, nums);

    memo.assign(n, -1); // reset: different subproblem
    int skipFirst = maxLoot(n - 1, 1, nums);

    return max(skipLast, skipFirst);
  }
};
