#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> result;
    vector<int> cur;
    backtrack(nums, 0, cur, result);
    return result;
  }

  void backtrack(vector<int> &nums, int idx, vector<int> &cur,
                 vector<vector<int>> &result) {
    if (idx == nums.size()) {
      result.push_back(cur);
      return;
    }
    // include nums[idx]
    cur.push_back(nums[idx]);
    backtrack(nums, idx + 1, cur, result);
    cur.pop_back(); // undo

    // skip nums[idx]
    backtrack(nums, idx + 1, cur, result);
  }
};
