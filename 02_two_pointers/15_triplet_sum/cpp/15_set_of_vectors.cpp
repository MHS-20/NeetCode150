#include <algorithm>
#include <set>
#include <vector>

using namespace std;
class Solution {
public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    set<vector<int>> triplets;
    sort(nums.begin(), nums.end());

    for (int idx = 0; idx < nums.size(); idx++) {
      int i = idx + 1, j = nums.size() - 1;

      while (i < j) {
        int sum = nums[idx] + nums[i] + nums[j];
        if (sum == 0) {
          triplets.insert({nums[idx], nums[i], nums[j]});
          i++;
          j--;
        }

        if (sum > 0)
          j--;
        if (sum < 0)
          i++;
      }
    }

    return vector<vector<int>>(triplets.begin(), triplets.end());
  }
};
