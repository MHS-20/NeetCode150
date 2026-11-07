impl Solution {
    pub fn change(amount: i32, coins: Vec<i32>) -> i32 {
        let amount = amount as usize;
        let mut dp = vec![0u64; amount + 1];
        dp[0] = 1;
        for &c in &coins {
            for x in c as usize..=amount {
                // wrapping: intermediates may overflow
                dp[x] = dp[x].wrapping_add(dp[x - c as usize]);
            }
        }
        dp[amount] as i32
    }
}
