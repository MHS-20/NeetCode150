impl Solution {
    pub fn unique_paths(m: i32, n: i32) -> i32 {
        let (m, n) = (m as usize, n as usize);
        let mut dp = vec![vec![0; n]; m];
        dp[m - 1][n - 1] = 1;

        for i in (0..m).rev() {
            for j in (0..n).rev() {
                if i == m - 1 && j == n - 1 {
                    continue;
                }
                let down = if i + 1 < m { dp[i + 1][j] } else { 0 };
                let right = if j + 1 < n { dp[i][j + 1] } else { 0 };
                dp[i][j] = down + right;
            }
        }
        dp[0][0]
    }
}
