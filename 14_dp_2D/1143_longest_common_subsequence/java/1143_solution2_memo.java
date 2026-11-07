import java.util.Arrays;

class Solution {
    private int solve(int i, int j, String a, String b, int[][] dp) {
        if (i == 0 || j == 0)
            return 0; // one string is empty
        if (dp[i][j] != -1)
            return dp[i][j];

        if (a.charAt(i - 1) == b.charAt(j - 1))
            return dp[i][j] = 1 + solve(i - 1, j - 1, a, b, dp);
        return dp[i][j] = Math.max(solve(i - 1, j, a, b, dp), solve(i, j - 1, a, b, dp));
    }

    public int longestCommonSubsequence(String text1, String text2) {
        int n = text1.length(), m = text2.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int[] row : dp)
            Arrays.fill(row, -1);
        return solve(n, m, text1, text2, dp);
    }
}
