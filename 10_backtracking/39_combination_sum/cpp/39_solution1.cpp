#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> result;
    vector<int> cur;
    backtrack(result, cur, 0, candidates, target, 0);
    return result;
  }

  void backtrack(vector<vector<int>> &result, vector<int> &cur, int idx,
                 vector<int> &candidates, int target, int sum) {
    if (sum == target) {
      result.push_back(cur);
      return;
    }
    if (sum > target || idx >= candidates.size())
      return;

    // include candidates[idx], stay on idx (can reuse it)
    cur.push_back(candidates[idx]);
    backtrack(result, cur, idx, candidates, target, sum + candidates[idx]);
    cur.pop_back();

    // skip candidates[idx] for good, move on
    backtrack(result, cur, idx + 1, candidates, target, sum);
  }
};
