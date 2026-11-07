#include <vector>

using namespace std;

class Solution {
public:
  vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    int n = edges.size();
    vector<int> parent(n + 1);
    for (int i = 1; i <= n; i++)
      parent[i] = i;

    for (auto &edge : edges) {
      int ra = find(parent, edge[0]);
      int rb = find(parent, edge[1]);
      if (ra == rb)
        return edge;
      parent[rb] = ra;
    }
    return {};
  }

private:
  int find(vector<int> &parent, int x) {
    while (parent[x] != x)
      x = parent[x];
    return x;
  }
};
