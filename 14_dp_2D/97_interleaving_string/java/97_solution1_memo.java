class Solution {
    private Boolean[][] dp; // null = not computed

    private boolean f(int i, int j, String s1, String s2, String s3) {
        if (i == s1.length() && j == s2.length())
            return true; // used everything
        if (dp[i][j] != null)
            return dp[i][j];

        int k = i + j; // position in s3
        boolean res = false;
        if (i < s1.length() && s1.charAt(i) == s3.charAt(k))
            res = f(i + 1, j, s1, s2, s3); // take from s1
        if (!res && j < s2.length() && s2.charAt(j) == s3.charAt(k))
            res = f(i, j + 1, s1, s2, s3); // take from s2

        return dp[i][j] = res;
    }

    public boolean isInterleave(String s1, String s2, String s3) {
        int n = s1.length(), m = s2.length();
        if (n + m != s3.length())
            return false;

        dp = new Boolean[n + 1][m + 1];
        return f(0, 0, s1, s2, s3);
    }
}
