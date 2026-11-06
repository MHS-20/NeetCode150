impl Solution {
    pub fn climb_stairs(n: i32) -> i32 {
        let n = n as usize;
        if n <= 2 {
            return n as i32;
        }

        let mut dp = vec![0; n + 1];
        dp[1] = 1;
        dp[2] = 2;

        for i in 3..=n {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        dp[n]
    }
}
