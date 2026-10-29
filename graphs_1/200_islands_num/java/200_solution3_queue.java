import java.util.ArrayDeque;
import java.util.Queue;

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
        Queue<int[]> q = new ArrayDeque<>();
        q.offer(new int[] {r, c});
        grid[r][c] = '0';
        while (!q.isEmpty()) {
            int[] cur = q.poll();
            for (int[] d : DIRS) {
                int nr = cur[0] + d[0], nc = cur[1] + d[1];
                if (nr >= 0 && nc >= 0 && nr < rows && nc < cols && grid[nr][nc] == '1') {
                    grid[nr][nc] = '0';
                    q.offer(new int[] {nr, nc});
                }
            }
        }
    }
}
