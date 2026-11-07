class Solution {
    private Boolean[][] dp; // null = not computed

    private boolean matches(String s, String p, int i, int j) { // s[i-1] vs p[j-1]
        return p.charAt(j - 1) == '.' || s.charAt(i - 1) == p.charAt(j - 1);
    }

    private boolean f(int i, int j, String s, String p) {
        if (j == 0)
            return i == 0; // empty pattern matches only empty s
        if (dp[i][j] != null)
            return dp[i][j];

        boolean res;
        if (p.charAt(j - 1) == '*') {
            res = f(i, j - 2, s, p); // zero copies
            if (!res && i > 0 && matches(s, p, i, j - 1))
                res = f(i - 1, j, s, p); // one more copy
        } else {
            res = i > 0 && matches(s, p, i, j) && f(i - 1, j - 1, s, p);
        }
        return dp[i][j] = res;
    }

    public boolean isMatch(String s, String p) {
        dp = new Boolean[s.length() + 1][p.length() + 1];
        return f(s.length(), p.length(), s, p);
    }
}
