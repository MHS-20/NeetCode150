impl Solution {
    pub fn num_decodings(s: String) -> i32 {
        let b = s.as_bytes();
        let n = b.len();
        let mut dp = vec![0; n + 1];
        dp[0] = 1;
        dp[1] = if b[0] != b'0' { 1 } else { 0 };

        for i in 2..=n {
            if b[i - 1] != b'0' {
                dp[i] += dp[i - 1];
            }

            let two = (b[i - 2] - b'0') * 10 + (b[i - 1] - b'0');
            if (10..=26).contains(&two) {
                dp[i] += dp[i - 2];
            }
        }
        dp[n]
    }
}
