#include <vector>
using namespace std;

class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    vector<int> prefixes(nums.size());
    vector<int> suffixes(nums.size());
    vector<int> ans(nums.size());

    prefixes[0] = 1;
    for (int i = 1; i < nums.size(); i++) {
      prefixes[i] = prefixes[i - 1] * nums[i - 1];
    }

    suffixes[nums.size() - 1] = 1;
    for (int i = nums.size() - 2; i >= 0; i--) {
      suffixes[i] = suffixes[i + 1] * nums[i + 1];
    }

    for (int i = 0; i < nums.size(); i++) {
      ans[i] = prefixes[i] * suffixes[i];
    }

    return ans;
  }
};
