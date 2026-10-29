#include <vector>

using namespace std;

class Solution {
public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    vector<vector<int>> adjacency(numCourses);
    for (const auto &p : prerequisites)
      adjacency[p[0]].push_back(p[1]);

    vector<int> state(numCourses, 0); // 0 = unvisited, 1 = on path, 2 = done
    for (int i = 0; i < numCourses; i++)
      if (!dfs(adjacency, state, i))
        return false;
    return true;
  }

private:
  bool dfs(const vector<vector<int>> &adjacency, vector<int> &state, int node) {
    if (state[node] == 1)
      return false; // back on the current path: cycle
    if (state[node] == 2)
      return true; // already fully explored

    state[node] = 1;
    for (int next : adjacency[node])
      if (!dfs(adjacency, state, next))
        return false;
    state[node] = 2;
    return true;
  }
};
