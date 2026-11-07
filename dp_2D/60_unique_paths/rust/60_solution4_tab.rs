impl Solution {
    pub fn unique_paths(m: i32, n: i32) -> i32 {
        let (m, n) = (m as usize, n as usize);
        let mut dp = vec![vec![0; n]; m];

        for i in 0..m {
            for j in 0..n {
                if i == 0 && j == 0 {
                    dp[i][j] = 1;
                    continue;
                }
                let up = if i > 0 { dp[i - 1][j] } else { 0 };
                let left = if j > 0 { dp[i][j - 1] } else { 0 };
                dp[i][j] = up + left;
            }
        }
        dp[m - 1][n - 1]
    }
}
