#include <stdlib.h>

static int find(const int *parent, int x) {
  while (parent[x] != x)
    x = parent[x];
  return x;
}

int *findRedundantConnection(int **edges, int edgesSize, int *edgesColSize,
                             int *returnSize) {
  (void)edgesColSize; // always 2
  int n = edgesSize;
  int *parent = malloc((n + 1) * sizeof(int));
  for (int i = 1; i <= n; i++)
    parent[i] = i;

  int *result = malloc(2 * sizeof(int));
  *returnSize = 0;
  for (int i = 0; i < edgesSize; i++) {
    int ra = find(parent, edges[i][0]);
    int rb = find(parent, edges[i][1]);
    if (ra == rb) {
      result[0] = edges[i][0], result[1] = edges[i][1];
      *returnSize = 2;
      break;
    }
    parent[rb] = ra;
  }

  free(parent);
  return result;
}
