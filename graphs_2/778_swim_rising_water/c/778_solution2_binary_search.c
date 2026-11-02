#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int n;
static int **g;
static bool *visited;
static int *queue; // cell indices r * n + c

static bool canReach(int t) {
  if (g[0][0] > t)
    return false;
  memset(visited, 0, n * n * sizeof(bool));
  int head = 0, tail = 0;
  queue[tail++] = 0;
  visited[0] = true;
  int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  while (head < tail) {
    int r = queue[head] / n, c = queue[head] % n;
    head++;
    if (r == n - 1 && c == n - 1)
      return true;
    for (int d = 0; d < 4; d++) {
      int nr = r + dirs[d][0], nc = c + dirs[d][1];
      if (nr < 0 || nc < 0 || nr >= n || nc >= n)
        continue;
      if (visited[nr * n + nc] || g[nr][nc] > t)
        continue;
      visited[nr * n + nc] = true;
      queue[tail++] = nr * n + nc;
    }
  }
  return false;
}

int swimInWater(int **grid, int gridSize, int *gridColSize) {
  (void)gridColSize; // square grid
  n = gridSize;
  g = grid;
  visited = malloc(n * n * sizeof(bool));
  queue = malloc(n * n * sizeof(int));

  int lo = 0, hi = n * n - 1;
  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (canReach(mid))
      hi = mid; // works: try lower
    else
      lo = mid + 1; // fails: need more water
  }

  free(visited);
  free(queue);
  return lo;
}
