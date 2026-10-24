#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> result;
    vector<int> cur(nums.begin(), nums.end());
    backtrack(nums, result, cur, 0);
    return result;
  }

  void backtrack(vector<int> &nums, vector<vector<int>> &result,
                 vector<int> &cur, int idx) {
    if (idx == nums.size()) {
      result.push_back(cur);
      return;
    }

    for (int i = idx; i < nums.size(); i++) {
      swap(cur[idx], cur[i]);
      backtrack(nums, result, cur, idx + 1);
      swap(cur[idx], cur[i]);
    }
  }
};
