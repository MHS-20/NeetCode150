#include <stdlib.h>

static const int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

static void sink(char **grid, int r, int c, int rows, int cols) {
  // each cell is pushed at most once, so rows * cols slots suffice
  int (*st)[2] = malloc(rows * cols * sizeof *st);
  int top = 0;
  st[top][0] = r, st[top][1] = c, top++;
  grid[r][c] = '0';
  while (top > 0) {
    top--;
    int cr = st[top][0], cc = st[top][1];
    for (int d = 0; d < 4; d++) {
      int nr = cr + dirs[d][0], nc = cc + dirs[d][1];
      if (nr >= 0 && nc >= 0 && nr < rows && nc < cols &&
          grid[nr][nc] == '1') {
        grid[nr][nc] = '0';
        st[top][0] = nr, st[top][1] = nc, top++;
      }
    }
  }
  free(st);
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
