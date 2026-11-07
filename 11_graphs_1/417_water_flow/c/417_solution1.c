#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

static const int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

static void dfs(int **heights, bool *ocean, int rows, int cols, int r, int c,
                int prevHeight) {
  if (r < 0 || c < 0 || r >= rows || c >= cols)
    return;
  if (ocean[r * cols + c] || heights[r][c] < prevHeight)
    return;

  ocean[r * cols + c] = true;
  for (int d = 0; d < 4; d++)
    dfs(heights, ocean, rows, cols, r + dirs[d][0], c + dirs[d][1],
        heights[r][c]);
}

int **pacificAtlantic(int **heights, int heightsSize, int *heightsColSize,
                      int *returnSize, int **returnColumnSizes) {
  int rows = heightsSize, cols = heightsColSize[0];
  // flattened rows x cols grids
  bool *pacific = calloc(rows * cols, sizeof(bool));
  bool *atlantic = calloc(rows * cols, sizeof(bool));

  for (int i = 0; i < rows; i++) {
    dfs(heights, pacific, rows, cols, i, 0, INT_MIN);
    dfs(heights, atlantic, rows, cols, i, cols - 1, INT_MIN);
  }
  for (int j = 0; j < cols; j++) {
    dfs(heights, pacific, rows, cols, 0, j, INT_MIN);
    dfs(heights, atlantic, rows, cols, rows - 1, j, INT_MIN);
  }

  // at most every cell qualifies
  int **result = malloc(rows * cols * sizeof(int *));
  *returnColumnSizes = malloc(rows * cols * sizeof(int));
  *returnSize = 0;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (pacific[i * cols + j] && atlantic[i * cols + j]) {
        int *cell = malloc(2 * sizeof(int));
        cell[0] = i, cell[1] = j;
        (*returnColumnSizes)[*returnSize] = 2;
        result[(*returnSize)++] = cell;
      }

  free(pacific);
  free(atlantic);
  return result;
}
