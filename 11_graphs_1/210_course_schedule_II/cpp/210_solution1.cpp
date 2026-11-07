#include <vector>

using namespace std;

class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<vector<int>> adjacency(numCourses);
    for (const auto &p : prerequisites)
      adjacency[p[0]].push_back(p[1]);

    vector<int> state(numCourses, 0); // 0 = unvisited, 1 = on path, 2 = done
    vector<int> order;
    for (int i = 0; i < numCourses; i++)
      if (!dfs(adjacency, state, i, order))
        return {};
    return order;
  }

private:
  bool dfs(const vector<vector<int>> &adjacency, vector<int> &state, int node,
           vector<int> &order) {
    if (state[node] == 1)
      return false; // cycle
    if (state[node] == 2)
      return true;

    state[node] = 1;
    for (int next : adjacency[node])
      if (!dfs(adjacency, state, next, order))
        return false;
    state[node] = 2;
    order.push_back(node);
    return true;
  }
};
