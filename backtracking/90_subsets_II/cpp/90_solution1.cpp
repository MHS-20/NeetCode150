#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<vector<int>> result;
    vector<int> cur;
    sort(nums.begin(), nums.end());
    backtrack(nums, 0, cur, result);
    return result;
  }

  void backtrack(vector<int> &nums, int idx, vector<int> &cur,
                 vector<vector<int>> &result) {
    if (idx == nums.size()) {
      result.push_back(cur);
      return;
    }

    cur.push_back(nums[idx]);
    backtrack(nums, idx + 1, cur, result);
    cur.pop_back();

    int i = idx + 1;
    while (i < nums.size() && nums[idx] == nums[i])
      i++;

    backtrack(nums, i, cur, result);
  }
};
