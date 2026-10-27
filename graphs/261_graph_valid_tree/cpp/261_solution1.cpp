#include <vector>

using namespace std;

class Solution {
public:
  bool validTree(int n, vector<vector<int>> &edges) {
    int count = n;
    vector<int> parent(n + 1);
    for (int i = 1; i <= n; i++)
      parent[i] = i;

    for (auto &edge : edges) {
      int ra = find(parent, edge[0]);
      int rb = find(parent, edge[1]);
      if (ra == rb)
        return false;
      else
        count--;
      parent[rb] = ra;
    }
    return count == 1;
  }

  int find(vector<int> &parent, int x) {
    while (parent[x] != x)
      x = parent[x];
    return x;
  }
};
