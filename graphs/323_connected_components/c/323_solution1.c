#include <stdlib.h>

static int find(const int *parent, int x) {
  while (parent[x] != x)
    x = parent[x];
  return x;
}

int countComponents(int n, int **edges, int edgesSize, int *edgesColSize) {
  (void)edgesColSize; // always 2
  int *parent = calloc(n + 1, sizeof(int));
  int count = n;
  for (int i = 1; i <= n; i++)
    parent[i] = i;

  for (int i = 0; i < edgesSize; i++) {
    int ra = find(parent, edges[i][0]);
    int rb = find(parent, edges[i][1]);
    if (ra != rb)
      count--;
    parent[rb] = ra;
  }

  free(parent);
  return count;
}
