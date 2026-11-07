#include <algorithm>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> minInterval(vector<vector<int>> &intervals,
                          vector<int> &queries) {
    vector<int> result(queries.size());
    vector<int> idx(queries.size());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;

    sort(intervals.begin(), intervals.end());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
         [&](int a, int b) { return queries[a] < queries[b]; });

    int i = 0, n = intervals.size();
    for (int j : idx) {
      int q = queries[j];

      while (i < n && intervals[i][0] <= q) {
        minHeap.push({intervals[i][1] - intervals[i][0] + 1, intervals[i][1]});
        i++;
      }

      while (!minHeap.empty() && minHeap.top().second < q)
        minHeap.pop();

      if (minHeap.empty())
        result[j] = -1;
      else
        result[j] = minHeap.top().first;
    }

    return result;
  }
};
