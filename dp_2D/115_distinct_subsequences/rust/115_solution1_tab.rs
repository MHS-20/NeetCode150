impl Solution {
    pub fn num_distinct(s: String, t: String) -> i32 {
        let (s, t) = (s.as_bytes(), t.as_bytes());
        let (n, m) = (s.len(), t.len());
        let mut dp = vec![vec![0u64; m + 1]; n + 1];
        for i in 0..=n {
            dp[i][0] = 1; // empty t: one way
        }

        for i in 1..=n {
            for j in 1..=m {
                dp[i][j] = dp[i - 1][j]; // skip cur s[i-1]
                if s[i - 1] == t[j - 1] {
                    // pick it; wrapping: intermediates may overflow
                    dp[i][j] = dp[i][j].wrapping_add(dp[i - 1][j - 1]);
                }
            }
        }
        dp[n][m] as i32
    }
}
