#include <limits.h>
#include <stdlib.h>
#include <string.h>

int findCheapestPrice(int n, int **flights, int flightsSize,
                      int *flightsColSize, int src, int dst, int k) {
  (void)flightsColSize; // always 3
  int *prices = malloc(n * sizeof(int));
  int *next = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    prices[i] = INT_MAX;
  prices[src] = 0;

  // Bellman-Ford limited to k + 1 rounds: round i allows i flights
  for (int round = 0; round <= k; round++) {
    memcpy(next, prices, n * sizeof(int)); // reads come from the previous round only
    for (int i = 0; i < flightsSize; i++) {
      int from = flights[i][0], to = flights[i][1], price = flights[i][2];
      if (prices[from] != INT_MAX && prices[from] + price < next[to])
        next[to] = prices[from] + price;
    }
    int *t = prices;
    prices = next;
    next = t;
  }

  int ans = prices[dst] == INT_MAX ? -1 : prices[dst];
  free(prices);
  free(next);
  return ans;
}
