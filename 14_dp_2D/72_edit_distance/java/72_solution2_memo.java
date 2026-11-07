import java.util.Arrays;

class Solution {
    private int f(int i, int j, String a, String b, int[][] dp) {
        if (i == 0)
            return j; // insert the remaining j chars
        if (j == 0)
            return i; // delete the remaining i chars
        if (dp[i][j] != -1)
            return dp[i][j];

        if (a.charAt(i - 1) == b.charAt(j - 1))
            return dp[i][j] = f(i - 1, j - 1, a, b, dp); // free match

        int del = f(i - 1, j, a, b, dp);
        int ins = f(i, j - 1, a, b, dp);
        int rep = f(i - 1, j - 1, a, b, dp);
        return dp[i][j] = 1 + Math.min(del, Math.min(ins, rep));
    }

    public int minDistance(String word1, String word2) {
        int n = word1.length(), m = word2.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int[] row : dp)
            Arrays.fill(row, -1);
        return f(n, m, word1, word2, dp);
    }
}
