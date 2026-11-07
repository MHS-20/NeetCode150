class Solution {
    public int change(int amount, int[] coins) {
        long[] dp = new long[amount + 1];
        dp[0] = 1;
        for (int c : coins)
            for (int x = c; x <= amount; x++)
                dp[x] += dp[x - c];
        return (int) dp[amount];
    }
}
