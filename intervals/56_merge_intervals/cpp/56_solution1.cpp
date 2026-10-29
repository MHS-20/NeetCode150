#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> result;

    for (const auto &cur : intervals) {
      if (result.empty() || result.back()[1] < cur[0])
        result.push_back(cur);
      else
        result.back()[1] = max(result.back()[1], cur[1]);
    }

    return result;
  }
};
