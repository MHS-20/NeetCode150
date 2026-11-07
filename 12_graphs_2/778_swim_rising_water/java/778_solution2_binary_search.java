import java.util.ArrayDeque;
import java.util.Queue;

class Solution {
    private int n;
    private int[][] grid;

    private boolean canReach(int t) {
        if (grid[0][0] > t)
            return false;
        boolean[][] visited = new boolean[n][n];
        Queue<int[]> q = new ArrayDeque<>();
        q.add(new int[] { 0, 0 });
        visited[0][0] = true;
        int[][] dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

        while (!q.isEmpty()) {
            int[] cur = q.poll();
            int r = cur[0], c = cur[1];
            if (r == n - 1 && c == n - 1)
                return true;
            for (int[] d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr < 0 || nc < 0 || nr >= n || nc >= n)
                    continue;
                if (visited[nr][nc] || grid[nr][nc] > t)
                    continue;
                visited[nr][nc] = true;
                q.add(new int[] { nr, nc });
            }
        }
        return false;
    }

    public int swimInWater(int[][] grid) {
        this.n = grid.length;
        this.grid = grid;
        int lo = 0, hi = n * n - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (canReach(mid))
                hi = mid; // works: try lower
            else
                lo = mid + 1; // fails: need more water
        }
        return lo;
    }
}
