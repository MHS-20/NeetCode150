#include <climits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                        int k) {
    vector<vector<pair<int, int>>> adj(n); // from -> {to, price}
    for (auto &f : flights)
      adj[f[0]].push_back({f[1], f[2]});

    vector<int> prices(n, INT_MAX);
    queue<pair<int, int>> q; // {city, cost so far}
    prices[src] = 0;
    q.push({src, 0});

    for (int flightsUsed = 0; flightsUsed <= k && !q.empty(); flightsUsed++) {
      int sz = q.size();
      for (int i = 0; i < sz; i++) {
        auto [c, p] = q.front();
        q.pop();
        for (auto [next, price] : adj[c]) {
          if (p + price < prices[next]) {
            prices[next] = p + price;
            q.push({next, p + price});
          }
        }
      }
    }

    return prices[dst] == INT_MAX ? -1 : prices[dst];
  }
};
