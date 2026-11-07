#include <cmath>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
    priority_queue<pair<double, vector<int>>> pq;

    for (auto &it : points) {
      double dist = sqrt(it[0] * it[0] + it[1] * it[1]);
      pq.push({dist, it});
      if (pq.size() > k)
        pq.pop();
    }

    vector<vector<int>> res;
    while (!pq.empty()) {
      res.push_back(pq.top().second);
      pq.pop();
    }

    return res;
  }
};
