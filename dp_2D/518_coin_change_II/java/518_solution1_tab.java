class Solution {
    public int change(int amount, int[] coins) {
        int n = coins.length;
        long[][] dp = new long[n + 1][amount + 1];
        for (int i = 0; i <= n; i++)
            dp[i][0] = 1; // one way to make 0: use nothing

        for (int i = 1; i <= n; i++) {
            for (int x = 1; x <= amount; x++) {
                dp[i][x] = dp[i - 1][x]; // skip coin i
                if (coins[i - 1] <= x)
                    dp[i][x] += dp[i][x - coins[i - 1]]; // take coin i (same row)
            }
        }
        return (int) dp[n][amount];
    }
}
