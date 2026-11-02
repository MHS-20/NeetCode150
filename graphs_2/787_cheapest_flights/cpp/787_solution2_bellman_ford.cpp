#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                        int k) {
    vector<int> prices(n, INT_MAX);
    prices[src] = 0;

    // Bellman-Ford limited to k + 1 rounds: round i allows i flights
    for (int round = 0; round <= k; round++) {
      vector<int> next = prices; // reads come from the previous round only
      for (auto &f : flights) {
        int from = f[0], to = f[1], price = f[2];
        if (prices[from] != INT_MAX && prices[from] + price < next[to])
          next[to] = prices[from] + price;
      }
      prices = move(next);
    }

    return prices[dst] == INT_MAX ? -1 : prices[dst];
  }
};
