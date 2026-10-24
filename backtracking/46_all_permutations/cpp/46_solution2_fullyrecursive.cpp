#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> result;
    backtrack(nums, result, 0, 0);
    return result;
  }

  void backtrack(vector<int> &nums, vector<vector<int>> &result, int idx,
                 int i) {
    if (idx == nums.size()) {
      result.push_back(nums);
      return;
    }
    if (i == nums.size())
      return;

    // choose nums[i] for position idx, then fix the next position
    swap(nums[idx], nums[i]);
    backtrack(nums, result, idx + 1, idx + 1);
    swap(nums[idx], nums[i]); // undo

    // try the next candidate for the same position
    backtrack(nums, result, idx, i + 1);
  }
};
