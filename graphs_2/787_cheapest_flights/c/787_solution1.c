#include <limits.h>
#include <stdlib.h>

typedef struct Edge {
  int to, price;
  struct Edge *next;
} Edge;

typedef struct {
  int city, cost;
} State;

int findCheapestPrice(int n, int **flights, int flightsSize,
                      int *flightsColSize, int src, int dst, int k) {
  (void)flightsColSize;
  // adjacency lists as linked lists; one edge node per flight
  Edge **adj = calloc(n, sizeof(Edge *));
  Edge *pool = malloc(flightsSize * sizeof(Edge));
  for (int i = 0; i < flightsSize; i++) {
    pool[i] = (Edge){flights[i][1], flights[i][2], adj[flights[i][0]]};
    adj[flights[i][0]] = &pool[i];
  }

  int *prices = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    prices[i] = INT_MAX;

  // a city can be queued more than once per level, so the buffers grow on demand
  int curCap = flightsSize + 1, nxtCap = flightsSize + 1;
  State *cur = malloc(curCap * sizeof(State));
  State *nxt = malloc(nxtCap * sizeof(State));
  int curSize = 0;
  prices[src] = 0;
  cur[curSize++] = (State){src, 0};

  for (int flightsUsed = 0; flightsUsed <= k && curSize > 0; flightsUsed++) {
    int nxtSize = 0;
    for (int i = 0; i < curSize; i++) {
      for (Edge *e = adj[cur[i].city]; e; e = e->next) {
        if (cur[i].cost + e->price < prices[e->to]) {
          prices[e->to] = cur[i].cost + e->price;
          if (nxtSize == nxtCap) {
            nxtCap *= 2;
            nxt = realloc(nxt, nxtCap * sizeof(State));
          }
          nxt[nxtSize++] = (State){e->to, prices[e->to]};
        }
      }
    }
    State *t = cur;
    cur = nxt;
    nxt = t;
    int c = curCap;
    curCap = nxtCap;
    nxtCap = c;
    curSize = nxtSize;
  }

  int ans = prices[dst] == INT_MAX ? -1 : prices[dst];
  free(adj);
  free(pool);
  free(prices);
  free(cur);
  free(nxt);
  return ans;
}
