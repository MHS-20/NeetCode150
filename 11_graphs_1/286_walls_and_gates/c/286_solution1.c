#include <limits.h>
#include <stdlib.h>

static const int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void islandsAndTreasure(int **grid, int gridSize, int *gridColSize) {
  int rows = gridSize, cols = gridColSize[0];
  // each cell is enqueued at most once, so rows * cols slots suffice
  int (*q)[2] = malloc(rows * cols * sizeof *q);
  int head = 0, tail = 0;

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (grid[i][j] == 0)
        q[tail][0] = i, q[tail][1] = j, tail++;

  while (head < tail) {
    int r = q[head][0], c = q[head][1];
    head++;
    for (int d = 0; d < 4; d++) {
      int nr = r + dirs[d][0], nc = c + dirs[d][1];
      if (nr < 0 || nc < 0 || nr >= rows || nc >= cols)
        continue;
      if (grid[nr][nc] != INT_MAX)
        continue;

      grid[nr][nc] = grid[r][c] + 1;
      q[tail][0] = nr, q[tail][1] = nc, tail++;
    }
  }

  free(q);
}
