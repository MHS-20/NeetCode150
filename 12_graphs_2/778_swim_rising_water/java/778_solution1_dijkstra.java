import java.util.PriorityQueue;

class Solution {
    public int swimInWater(int[][] grid) {
        int n = grid.length;
        boolean[][] visited = new boolean[n][n];
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0])); // {elev, r, c}
        int[][] dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

        pq.add(new int[] { grid[0][0], 0, 0 });
        visited[0][0] = true;
        int t = 0;

        while (!pq.isEmpty()) {
            int[] e = pq.poll();
            int elev = e[0], r = e[1], c = e[2];
            t = Math.max(t, elev);
            if (r == n - 1 && c == n - 1)
                return t;

            for (int[] d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr < 0 || nc < 0 || nr >= n || nc >= n || visited[nr][nc])
                    continue;
                visited[nr][nc] = true;
                pq.add(new int[] { grid[nr][nc], nr, nc });
            }
        }
        return -1;
    }
}
