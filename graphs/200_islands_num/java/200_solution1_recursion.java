class Solution {
    public int numIslands(char[][] grid) {
        if (grid.length == 0)
            return 0;
        int rows = grid.length, cols = grid[0].length;
        int count = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (grid[i][j] == '1') {
                    sink(grid, i, j, rows, cols);
                    count++;
                }
        return count;
    }

    private static final int[][] DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    private void sink(char[][] grid, int r, int c, int rows, int cols) {
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] != '1')
            return;
        grid[r][c] = '0';
        for (int[] d : DIRS)
            sink(grid, r + d[0], c + d[1], rows, cols);
    }
}
