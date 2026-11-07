impl Solution {
    pub fn is_match(s: String, p: String) -> bool {
        let (s, p) = (s.as_bytes(), p.as_bytes());
        let (n, m) = (s.len(), p.len());
        let mut dp = vec![vec![false; m + 1]; n + 1];
        dp[0][0] = true;

        let matches = |i: usize, j: usize| p[j - 1] == b'.' || s[i - 1] == p[j - 1]; // s[i-1] vs p[j-1]

        for i in 0..=n {
            for j in 1..=m {
                if p[j - 1] == b'*' {
                    dp[i][j] = dp[i][j - 2]; // zero copies
                    if i > 0 && matches(i, j - 1) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j]; // one more copy
                    }
                } else {
                    dp[i][j] = i > 0 && matches(i, j) && dp[i - 1][j - 1];
                }
            }
        }
        dp[n][m]
    }
}
