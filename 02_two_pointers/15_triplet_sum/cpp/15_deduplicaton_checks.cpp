#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());

    for (int idx = 0; idx < nums.size(); idx++) {
      if (idx > 0 && nums[idx] == nums[idx - 1])
        continue; // skip duplicate fixed value

      int i = idx + 1, j = nums.size() - 1;
      while (i < j) {
        int sum = nums[idx] + nums[i] + nums[j];
        if (sum == 0) {
          result.push_back({nums[idx], nums[i], nums[j]});
          i++;
          j--;
          while (i < j && nums[i] == nums[i - 1])
            i++; // skip duplicate left values
          while (i < j && nums[j] == nums[j + 1])
            j--; // skip duplicate right values
        } else if (sum > 0) {
          j--;
        } else {
          i++;
        }
      }
    }

    return result;
  }
};
