impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        let (a, b) = (word1.as_bytes(), word2.as_bytes());
        let (n, m) = (a.len(), b.len());
        let mut dp = vec![vec![0; m + 1]; n + 1];

        for i in 0..=n {
            dp[i][0] = i as i32; // delete all
        }
        for j in 0..=m {
            dp[0][j] = j as i32; // insert all
        }

        for i in 1..=n {
            for j in 1..=m {
                dp[i][j] = if a[i - 1] == b[j - 1] {
                    dp[i - 1][j - 1]
                } else {
                    1 + dp[i - 1][j] // delete
                        .min(dp[i][j - 1]) // insert
                        .min(dp[i - 1][j - 1]) // replace
                };
            }
        }
        dp[n][m]
    }
}
