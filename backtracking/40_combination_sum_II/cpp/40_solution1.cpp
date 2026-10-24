#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    vector<vector<int>> result;
    vector<int> cur;
    sort(candidates.begin(), candidates.end());
    backtrack(candidates, 0, 0, target, cur, result);
    return result;
  }

  void backtrack(vector<int> &candidates, int idx, int sum, int &target,
                 vector<int> &cur, vector<vector<int>> &result) {
    if (sum == target) {
      result.push_back(cur);
      return;
    }

    if (sum > target || idx == candidates.size())
      return;

    cur.push_back(candidates[idx]);
    backtrack(candidates, idx + 1, sum + candidates[idx], target, cur, result);
    cur.pop_back();

    int i = idx + 1;
    while (i < candidates.size() && candidates[i] == candidates[idx])
      i++;
    backtrack(candidates, i, sum, target, cur, result);
  }
};
