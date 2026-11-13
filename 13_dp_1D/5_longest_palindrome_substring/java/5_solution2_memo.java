class Solution {
    private Boolean[][] memo; // null unknown

    public String longestPalindrome(String s) {
        int n = s.length();
        memo = new Boolean[n][n];
        int bestStart = 0, bestLen = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (j - i + 1 > bestLen && isPal(s, i, j)) {
                    bestLen = j - i + 1;
                    bestStart = i;
                }
            }
        }
        return s.substring(bestStart, bestStart + bestLen);
    }

    private boolean isPal(String s, int i, int j) {
        if (i >= j)
            return true; // length 0 or 1
        if (memo[i][j] == null)
            memo[i][j] = s.charAt(i) == s.charAt(j) && isPal(s, i + 1, j - 1);
        return memo[i][j];
    }
}
