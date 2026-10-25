#include <stdlib.h>

static const int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

static void sink(char **grid, int r, int c, int rows, int cols) {
  // each cell is enqueued at most once, so rows * cols slots suffice
  int (*q)[2] = malloc(rows * cols * sizeof *q);
  int head = 0, tail = 0;
  q[tail][0] = r, q[tail][1] = c, tail++;
  grid[r][c] = '0';
  while (head < tail) {
    int cr = q[head][0], cc = q[head][1];
    head++;
    for (int d = 0; d < 4; d++) {
      int nr = cr + dirs[d][0], nc = cc + dirs[d][1];
      if (nr >= 0 && nc >= 0 && nr < rows && nc < cols &&
          grid[nr][nc] == '1') {
        grid[nr][nc] = '0';
        q[tail][0] = nr, q[tail][1] = nc, tail++;
      }
    }
  }
  free(q);
}

int numIslands(char **grid, int gridSize, int *gridColSize) {
  if (gridSize == 0)
    return 0;
  int rows = gridSize, cols = gridColSize[0];
  int count = 0;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (grid[i][j] == '1') {
        sink(grid, i, j, rows, cols);
        count++;
      }
  return count;
}
