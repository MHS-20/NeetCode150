#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProduct(vector<int> &nums) {
    int curMax = nums[0], curMin = nums[0], best = nums[0];

    for (int i = 1; i < (int)nums.size(); i++) {
      int x = nums[i];
      int a = curMax * x, b = curMin * x;

      curMax = max({x, a, b});
      curMin = min({x, a, b});
      best = max(best, curMax);
    }
    return best;
  }
};
