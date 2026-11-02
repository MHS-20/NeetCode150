#include <stdlib.h>

static int *parent, *rnk;

static int find(int x) {
  while (parent[x] != x) {
    parent[x] = parent[parent[x]]; // path halving
    x = parent[x];
  }
  return x;
}

static void unite(int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b)
    return;
  if (rnk[a] < rnk[b]) {
    int t = a;
    a = b;
    b = t;
  }
  parent[b] = a;
  if (rnk[a] == rnk[b])
    rnk[a]++;
}

int swimInWater(int **grid, int gridSize, int *gridColSize) {
  (void)gridColSize; // square grid
  int n = gridSize;
  parent = malloc(n * n * sizeof(int));
  rnk = calloc(n * n, sizeof(int));
  for (int i = 0; i < n * n; i++)
    parent[i] = i;

  // pos[v] = cell index holding elevation v
  int *pos = malloc(n * n * sizeof(int));
  for (int r = 0; r < n; r++)
    for (int c = 0; c < n; c++)
      pos[grid[r][c]] = r * n + c;

  int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  int ans = -1;

  for (int t = 0; t < n * n && ans == -1; t++) {
    int r = pos[t] / n, c = pos[t] % n; // this cell becomes submerged
    for (int d = 0; d < 4; d++) {
      int nr = r + dirs[d][0], nc = c + dirs[d][1];
      if (nr < 0 || nc < 0 || nr >= n || nc >= n)
        continue;
      if (grid[nr][nc] <= t) // neighbor already submerged
        unite(r * n + c, nr * n + nc);
    }
    if (find(0) == find(n * n - 1))
      ans = t;
  }

  free(parent);
  free(rnk);
  free(pos);
  return ans;
}
