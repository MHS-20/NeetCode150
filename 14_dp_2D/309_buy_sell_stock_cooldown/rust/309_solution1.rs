impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let n = prices.len();
        let mut dp = vec![[0; 2]; n + 2]; // dp[day][can_buy]

        for day in (0..n).rev() {
            // can_buy = 1
            dp[day][1] = (-prices[day] + dp[day + 1][0]) // buy
                .max(dp[day + 1][1]); // skip
            // can_buy = 0 (holding)
            dp[day][0] = (prices[day] + dp[day + 2][1]) // sell + cooldown
                .max(dp[day + 1][0]); // hold
        }
        dp[0][1]
    }
}
