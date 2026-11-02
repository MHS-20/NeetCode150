#include <algorithm>
#include <climits>
#include <cstdlib>
#include <vector>

using namespace std;

class Solution {
public:
  int minCostConnectPoints(vector<vector<int>> &points) {
    int n = points.size();
    vector<int> minCost(n, INT_MAX);
    vector<bool> inTree(n, false);
    minCost[0] = 0;
    int cost = 0;

    for (int step = 0; step < n; step++) {
      // 1. Pick the cheapest point not yet in the tree
      int u = -1;
      for (int i = 0; i < n; i++)
        if (!inTree[i] && (u == -1 || minCost[i] < minCost[u]))
          u = i;

      // 2. Add it
      inTree[u] = true;
      cost += minCost[u];

      // 3. Update the outside points' best connection
      for (int i = 0; i < n; i++) {
        if (inTree[i])
          continue;
        int dist =
            abs(points[i][0] - points[u][0]) + abs(points[i][1] - points[u][1]);
        minCost[i] = min(minCost[i], dist);
      }
    }
    return cost;
  }
};
