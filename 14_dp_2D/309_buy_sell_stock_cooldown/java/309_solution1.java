class Solution {
    public int maxProfit(int[] prices) {
        int n = prices.length;
        int[][] dp = new int[n + 2][2]; // dp[day][canBuy]

        for (int day = n - 1; day >= 0; day--) {
            // canBuy = 1
            dp[day][1] = Math.max(-prices[day] + dp[day + 1][0], // buy
                    dp[day + 1][1]); // skip
            // canBuy = 0 (holding)
            dp[day][0] = Math.max(prices[day] + dp[day + 2][1], // sell + cooldown
                    dp[day + 1][0]); // hold
        }
        return dp[0][1];
    }
}
