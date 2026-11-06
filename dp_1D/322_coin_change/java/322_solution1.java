import java.util.Arrays;

class Solution {
    public int coinChange(int[] coins, int amount) {
        int INF = amount + 1;
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, INF);
        dp[0] = 0;

        for (int x = 1; x <= amount; x++) {
            for (int c : coins) {
                if (c <= x && dp[x - c] != INF) {
                    dp[x] = Math.min(dp[x], dp[x - c] + 1);
                }
            }
        }
        return dp[amount] == INF ? -1 : dp[amount];
    }
}
