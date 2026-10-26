import java.util.ArrayDeque;
import java.util.Queue;

class Solution {
    private static final int[][] DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    public int orangesRotting(int[][] grid) {
        int rows = grid.length, cols = grid[0].length;
        Queue<int[]> q = new ArrayDeque<>();
        int fresh = 0;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 2)
                    q.offer(new int[] {i, j});
                else if (grid[i][j] == 1)
                    fresh++;
            }

        int minutes = 0;
        while (!q.isEmpty() && fresh > 0) {
            int sz = q.size();
            minutes++;
            for (int k = 0; k < sz; k++) {
                int[] cur = q.poll();
                int r = cur[0], c = cur[1];
                for (int[] d : DIRS) {
                    int nr = r + d[0], nc = c + d[1];
                    if (nr < 0 || nc < 0 || nr >= rows || nc >= cols)
                        continue;
                    if (grid[nr][nc] != 1)
                        continue;

                    grid[nr][nc] = 2;
                    fresh--;
                    q.offer(new int[] {nr, nc});
                }
            }
        }
        return fresh == 0 ? minutes : -1;
    }
}
