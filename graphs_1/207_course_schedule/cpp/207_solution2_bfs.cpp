#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    vector<vector<int>> unlocks(numCourses); // b -> courses that need b
    vector<int> remaining(numCourses, 0);    // prerequisites still missing

    for (auto &p : prerequisites) {
      int a = p[0], b = p[1];
      unlocks[b].push_back(a);
      remaining[a]++;
    }

    queue<int> q;
    for (int c = 0; c < numCourses; c++)
      if (remaining[c] == 0)
        q.push(c);

    int taken = 0;
    while (!q.empty()) {
      int c = q.front();
      q.pop();
      taken++;

      for (int next : unlocks[c])
        if (--remaining[next] == 0)
          q.push(next);
    }

    return taken == numCourses;
  }
};
