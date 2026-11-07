import java.util.Arrays;

class Solution {
    private long[][] dp; // -1 = not computed

    private long f(int i, int j, String s, String t) {
        if (j == 0)
            return 1; // t fully matched
        if (i == 0)
            return 0; // s ran out first
        if (dp[i][j] != -1)
            return dp[i][j];

        long ways = f(i - 1, j, s, t); // skip s[i-1]
        if (s.charAt(i - 1) == t.charAt(j - 1))
            ways += f(i - 1, j - 1, s, t); // pick it

        // keep within u32 range so nothing overflows and -1 stays a free sentinel
        return dp[i][j] = ways & 0xFFFFFFFFL;
    }

    public int numDistinct(String s, String t) {
        int n = s.length(), m = t.length();
        dp = new long[n + 1][m + 1];
        for (long[] row : dp)
            Arrays.fill(row, -1);
        return (int) f(n, m, s, t);
    }
}
