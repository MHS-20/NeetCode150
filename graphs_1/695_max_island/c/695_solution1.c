static const int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

static void sink(int **grid, int r, int c, int rows, int cols, int *count) {
  if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] != 1)
    return;
  grid[r][c] = 0;
  (*count)++;
  for (int d = 0; d < 4; d++)
    sink(grid, r + dirs[d][0], c + dirs[d][1], rows, cols, count);
}

int maxAreaOfIsland(int **grid, int gridSize, int *gridColSize) {
  if (gridSize == 0)
    return 0;

  int mx = 0, count = 0;
  int rows = gridSize, cols = gridColSize[0];

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (grid[i][j] == 1) {
        count = 0;
        sink(grid, i, j, rows, cols, &count);
        if (count > mx)
          mx = count;
      }
  return mx;
}
