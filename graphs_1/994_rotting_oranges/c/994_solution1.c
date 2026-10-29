#include <stdlib.h>

int orangesRotting(int **grid, int gridSize, int *gridColSize) {
  static const int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  int rows = gridSize, cols = gridColSize[0];
  // each cell is enqueued at most once, so rows * cols slots suffice
  int (*q)[2] = malloc(rows * cols * sizeof *q);
  int head = 0, tail = 0;
  int fresh = 0;

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == 2)
        q[tail][0] = i, q[tail][1] = j, tail++;
      else if (grid[i][j] == 1)
        fresh++;
    }

  int minutes = 0;
  while (head < tail && fresh > 0) {
    int levelEnd = tail;
    minutes++;
    while (head < levelEnd) {
      int r = q[head][0], c = q[head][1];
      head++;
      for (int d = 0; d < 4; d++) {
        int nr = r + dirs[d][0], nc = c + dirs[d][1];
        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols)
          continue;
        if (grid[nr][nc] != 1)
          continue;

        grid[nr][nc] = 2;
        fresh--;
        q[tail][0] = nr, q[tail][1] = nc, tail++;
      }
    }
  }

  free(q);
  return fresh == 0 ? minutes : -1;
}
