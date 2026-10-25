class Solution {
    private static final int[][] DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    private int count;

    public int maxAreaOfIsland(int[][] grid) {
        if (grid.length == 0)
            return 0;

        int mx = 0;
        int rows = grid.length, cols = grid[0].length;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (grid[i][j] == 1) {
                    count = 0;
                    sink(grid, i, j, rows, cols);
                    mx = Math.max(count, mx);
                }
        return mx;
    }

    private void sink(int[][] grid, int r, int c, int rows, int cols) {
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] != 1)
            return;
        grid[r][c] = 0;
        count++;
        for (int[] d : DIRS)
            sink(grid, r + d[0], c + d[1], rows, cols);
    }
}
