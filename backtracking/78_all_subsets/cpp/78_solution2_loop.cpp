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

  void backtrack(vector<int> &nums, int start, vector<int> &cur,
                 vector<vector<int>> &result) {
    result.push_back(cur); // every path is a valid subset

    for (int i = start; i < nums.size(); i++) {
      cur.push_back(nums[i]);
      backtrack(nums, i + 1, cur, result);
      cur.pop_back(); // undo
    }
  }
};
