class Solution {
    public String longestPalindrome(String s) {
        int n = s.length(), bestLen = 0, bestStart = 0;
        boolean[][] memo = new boolean[n][n];

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s.charAt(i) == s.charAt(j) && (j - i < 2 || memo[i + 1][j - 1])) {
                    memo[i][j] = true;
                    if (j - i + 1 > bestLen) {
                        bestLen = j - i + 1;
                        bestStart = i;
                    }
                }
            }
        }

        return s.substring(bestStart, bestStart + bestLen);
    }
}
