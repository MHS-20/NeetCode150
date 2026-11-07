impl Solution {
    pub fn unique_paths(m: i32, n: i32) -> i32 {
        let mut dp = vec![vec![-1; n as usize]; m as usize];
        Self::solve(m - 1, n - 1, &mut dp)
    }

    // i, j are i32 so they can step below 0 without underflow
    fn solve(i: i32, j: i32, dp: &mut Vec<Vec<i32>>) -> i32 {
        if i == 0 && j == 0 {
            return 1; // reached the start
        }
        if i < 0 || j < 0 {
            return 0; // fell off the grid
        }
        let (r, c) = (i as usize, j as usize);
        if dp[r][c] != -1 {
            return dp[r][c]; // already computed
        }

        let up = Self::solve(i - 1, j, dp);
        let left = Self::solve(i, j - 1, dp);
        dp[r][c] = up + left;
        dp[r][c]
    }
}
