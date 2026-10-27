#include <stdbool.h>
#include <stdlib.h>

static int find(const int *parent, int x) {
  while (parent[x] != x)
    x = parent[x];
  return x;
}

bool validTree(int n, int **edges, int edgesSize, int *edgesColSize) {
  (void)edgesColSize; // always 2
  int count = n;
  int *parent = calloc(n + 1, sizeof(int));
  for (int i = 1; i <= n; i++)
    parent[i] = i;

  bool ok = true;
  for (int i = 0; i < edgesSize; i++) {
    int ra = find(parent, edges[i][0]);
    int rb = find(parent, edges[i][1]);
    if (ra == rb) {
      ok = false; // cycle
      break;
    }
    count--;
    parent[rb] = ra;
  }

  free(parent);
  return ok && count == 1;
}
