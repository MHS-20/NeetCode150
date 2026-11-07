#include <algorithm>
#include <functional>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<string, priority_queue<string, vector<string>, greater<>>> adj;
  vector<string> result;

  void dfs(const string &cur) {
    auto &dests = adj[cur];
    while (!dests.empty()) {
      string next = dests.top();
      dests.pop(); // use this ticket
      dfs(next);
    }
    result.push_back(cur); // post-order: no tickets left here
  }

public:
  vector<string> findItinerary(vector<vector<string>> &tickets) {
    for (auto &t : tickets)
      adj[t[0]].push(t[1]);

    dfs("JFK");
    reverse(result.begin(), result.end());
    return result;
  }
};
