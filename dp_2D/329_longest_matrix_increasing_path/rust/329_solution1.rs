impl Solution {
    pub fn longest_increasing_path(matrix: Vec<Vec<i32>>) -> i32 {
        let (m, n) = (matrix.len(), matrix[0].len());
        let mut dp = vec![vec![0; n]; m]; // 0 = not computed

        let mut res = 0;
        for i in 0..m {
            for j in 0..n {
                res = res.max(Self::dfs(i, j, &matrix, &mut dp));
            }
        }
        res
    }

    fn dfs(i: usize, j: usize, matrix: &[Vec<i32>], dp: &mut Vec<Vec<i32>>) -> i32 {
        if dp[i][j] != 0 {
            return dp[i][j]; // already computed
        }

        let (m, n) = (matrix.len() as i32, matrix[0].len() as i32);
        let mut best = 1; // the cell alone
        for (di, dj) in [(1, 0), (-1, 0), (0, 1), (0, -1)] {
            let (ni, nj) = (i as i32 + di, j as i32 + dj);
            if ni >= 0 && ni < m && nj >= 0 && nj < n {
                let (ni, nj) = (ni as usize, nj as usize);
                if matrix[ni][nj] > matrix[i][j] {
                    best = best.max(1 + Self::dfs(ni, nj, matrix, dp));
                }
            }
        }
        dp[i][j] = best;
        best
    }
}
