impl Solution {
    pub fn min_cost_climbing_stairs(cost: Vec<i32>) -> i32 {
        let n = cost.len();
        let mut dp = vec![0; n + 1]; // dp[0] = dp[1] = 0: start on step 0 or 1 for free

        for i in 2..=n {
            dp[i] = (dp[i - 1] + cost[i - 1]).min(dp[i - 2] + cost[i - 2]);
        }
        dp[n] // n = the top, one past the last step
    }
}
