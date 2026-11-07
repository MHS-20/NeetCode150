#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> seen;
    seen.reserve(nums.size());

    for (int i = 0; i < (int)nums.size(); i++) {
      auto it = seen.find(nums[i]);
      if (it != seen.end()) {
        return {it->second, i};
      }
      seen[target - nums[i]] = i;
    }
    return {};
  }
};
