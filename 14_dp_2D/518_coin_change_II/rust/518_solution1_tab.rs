impl Solution {
    pub fn change(amount: i32, coins: Vec<i32>) -> i32 {
        let (n, amount) = (coins.len(), amount as usize);
        let mut dp = vec![vec![0u64; amount + 1]; n + 1];
        for i in 0..=n {
            dp[i][0] = 1; // one way to make 0: use nothing
        }

        for i in 1..=n {
            let c = coins[i - 1] as usize;
            for x in 1..=amount {
                dp[i][x] = dp[i - 1][x]; // skip coin i
                if c <= x {
                    // take coin i (same row); wrapping: intermediates may overflow
                    dp[i][x] = dp[i][x].wrapping_add(dp[i][x - c]);
                }
            }
        }
        dp[n][amount] as i32
    }
}
