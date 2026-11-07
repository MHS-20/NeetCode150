#include <algorithm>
#include <climits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  int networkDelayTime(vector<vector<int>> &times, int n, int k) {
    vector<vector<pair<int, int>>> adj(n + 1); // node -> {neighbor, weight}
    for (auto &t : times)
      adj[t[0]].push_back({t[1], t[2]});

    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>
        pq; // {dist, node}
    dist[k] = 0;
    pq.push({0, k});

    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (d > dist[u])
        continue; // stale entry
      for (auto [v, w] : adj[u]) {
        if (d + w < dist[v]) {
          dist[v] = d + w;
          pq.push({dist[v], v});
        }
      }
    }

    int ans = *max_element(dist.begin() + 1, dist.end());
    return ans == INT_MAX ? -1 : ans;
  }
};
