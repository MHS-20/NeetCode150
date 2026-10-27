#include <vector>

using namespace std;

class Solution {
public:
  int countComponents(int n, vector<vector<int>> &edges) {
    vector<int> parent(n + 1);
    int count = n;
    for (int i = 1; i <= n; i++)
      parent[i] = i;

    for (auto &edge : edges) {
      int ra = find(parent, edge[0]);
      int rb = find(parent, edge[1]);
      if (ra != rb)
        count--;
      parent[rb] = ra;
    }
    return count;
  }

  int find(vector<int> &parent, int x) {
    while (parent[x] != x)
      x = parent[x];
    return x;
  }
};
