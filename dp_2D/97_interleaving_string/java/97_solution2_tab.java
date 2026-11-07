class Solution {
    public boolean isInterleave(String s1, String s2, String s3) {
        int n = s1.length(), m = s2.length();
        if (n + m != s3.length())
            return false;

        boolean[][] dp = new boolean[n + 1][m + 1];
        dp[0][0] = true; // empty + empty = empty

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0)
                    continue;
                int k = i + j - 1; // last char of s3 prefix
                boolean fromS1 = i > 0 && dp[i - 1][j] && s1.charAt(i - 1) == s3.charAt(k);
                boolean fromS2 = j > 0 && dp[i][j - 1] && s2.charAt(j - 1) == s3.charAt(k);
                dp[i][j] = fromS1 || fromS2;
            }
        }
        return dp[n][m];
    }
}
