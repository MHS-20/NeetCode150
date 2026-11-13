class Solution {
    public int countSubstrings(String s) {
        int n = s.length(), count = 0;
        boolean[][] memo = new boolean[n][n];

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s.charAt(i) == s.charAt(j) && (j - i < 2 || memo[i + 1][j - 1])) {
                    memo[i][j] = true;
                    count++;
                }
            }
        }

        return count;
    }
}
