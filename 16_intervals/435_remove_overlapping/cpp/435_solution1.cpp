#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    vector<vector<int>> result;
    sort(intervals.begin(), intervals.end());

    for (int i = 0; i < intervals.size(); i++) {
      if (result.empty() || result.back()[1] <= intervals[i][0]) {
        result.push_back(intervals[i]);
        continue;
      }

      if (result.back()[1] > intervals[i][1]) {
        result.pop_back();
        result.push_back(intervals[i]);
      }
    }

    return intervals.size() - result.size();
  }
};
