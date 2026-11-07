class Solution {
    public int numDistinct(String s, String t) {
        int n = s.length(), m = t.length();
        long[][] dp = new long[n + 1][m + 1];
        for (int i = 0; i <= n; i++)
            dp[i][0] = 1; // empty t: one way

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = dp[i - 1][j]; // skip cur s[i-1]
                if (s.charAt(i - 1) == t.charAt(j - 1))
                    dp[i][j] += dp[i - 1][j - 1]; // pick it
            }
        }
        return (int) dp[n][m];
    }
}
