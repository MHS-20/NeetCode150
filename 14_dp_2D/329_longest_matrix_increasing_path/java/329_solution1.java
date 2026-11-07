class Solution {
    private int m, n;
    private static final int[][] DIRS = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

    private int dfs(int i, int j, int[][] matrix, int[][] dp) {
        if (dp[i][j] != 0)
            return dp[i][j]; // already computed

        int best = 1; // the cell alone
        for (int[] d : DIRS) {
            int ni = i + d[0], nj = j + d[1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && matrix[ni][nj] > matrix[i][j]) {
                best = Math.max(best, 1 + dfs(ni, nj, matrix, dp));
            }
        }
        return dp[i][j] = best;
    }

    public int longestIncreasingPath(int[][] matrix) {
        m = matrix.length;
        n = matrix[0].length;
        int[][] dp = new int[m][n];

        int res = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                res = Math.max(res, dfs(i, j, matrix, dp));
        return res;
    }
}
