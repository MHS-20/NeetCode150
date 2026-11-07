import java.util.Arrays;

class Solution {
    private int solve(int i, int j, int[][] dp) {
        if (i == 0 && j == 0)
            return 1; // reached the start
        if (i < 0 || j < 0)
            return 0; // fell off the grid
        if (dp[i][j] != -1)
            return dp[i][j]; // already computed

        int up = solve(i - 1, j, dp);
        int left = solve(i, j - 1, dp);
        return dp[i][j] = up + left;
    }

    public int uniquePaths(int m, int n) {
        int[][] dp = new int[m][n];
        for (int[] row : dp)
            Arrays.fill(row, -1);
        return solve(m - 1, n - 1, dp);
    }
}
