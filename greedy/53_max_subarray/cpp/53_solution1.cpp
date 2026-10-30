#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
  int maxSubArray(vector<int> &nums) {
    int sum = 0;
    int mx = INT_MIN;

    for (int i = 0; i < nums.size(); i++) {
      sum += nums[i];
      mx = max(sum, mx);
      if (sum < 0)
        sum = nums[i] < 0 ? 0 : nums[i];
    }

    return mx;
  }
};
