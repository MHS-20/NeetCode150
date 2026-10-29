import java.util.ArrayDeque;
import java.util.Queue;

class Solution {
    private static final int[][] DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    public void islandsAndTreasure(int[][] grid) {
        int rows = grid.length, cols = grid[0].length;
        Queue<int[]> q = new ArrayDeque<>();

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (grid[i][j] == 0)
                    q.offer(new int[] {i, j});

        while (!q.isEmpty()) {
            int[] cur = q.poll();
            int r = cur[0], c = cur[1];
            for (int[] d : DIRS) {
                int nr = r + d[0], nc = c + d[1];
                if (nr < 0 || nc < 0 || nr >= rows || nc >= cols)
                    continue;
                if (grid[nr][nc] != Integer.MAX_VALUE)
                    continue;

                grid[nr][nc] = grid[r][c] + 1;
                q.offer(new int[] {nr, nc});
            }
        }
    }
}
