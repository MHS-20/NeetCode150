#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int minCostConnectPoints(int **points, int pointsSize, int *pointsColSize) {
  (void)pointsColSize; // always 2
  int n = pointsSize;
  int *minCost = malloc(n * sizeof(int));
  bool *inTree = calloc(n, sizeof(bool));
  for (int i = 0; i < n; i++)
    minCost[i] = INT_MAX;
  minCost[0] = 0;
  int cost = 0;

  for (int step = 0; step < n; step++) {
    // 1. Pick the cheapest point not yet in the tree
    int u = -1;
    for (int i = 0; i < n; i++)
      if (!inTree[i] && (u == -1 || minCost[i] < minCost[u]))
        u = i;

    // 2. Add it
    inTree[u] = true;
    cost += minCost[u];

    // 3. Update the outside points' best connection
    for (int i = 0; i < n; i++) {
      if (inTree[i])
        continue;
      int dist =
          abs(points[i][0] - points[u][0]) + abs(points[i][1] - points[u][1]);
      if (dist < minCost[i])
        minCost[i] = dist;
    }
  }

  free(minCost);
  free(inTree);
  return cost;
}
