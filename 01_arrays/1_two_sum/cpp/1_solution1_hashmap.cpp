#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> map;

    for (int i = 0; i < nums.size(); i++) {
      if (map.find(nums[i]) != map.end()) {
        return {map[nums[i]], i};
      } else {
        map[target - nums[i]] = i;
      }
    }

    return {};
  }
};
