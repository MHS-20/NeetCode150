impl Solution {
    pub fn longest_common_subsequence(text1: String, text2: String) -> i32 {
        let (a, b) = (text1.as_bytes(), text2.as_bytes());
        let (n, m) = (a.len(), b.len());
        let mut dp = vec![vec![0; m + 1]; n + 1];

        for i in 1..=n {
            for j in 1..=m {
                dp[i][j] = if a[i - 1] == b[j - 1] {
                    1 + dp[i - 1][j - 1]
                } else {
                    dp[i - 1][j].max(dp[i][j - 1])
                };
            }
        }
        dp[n][m]
    }
}
