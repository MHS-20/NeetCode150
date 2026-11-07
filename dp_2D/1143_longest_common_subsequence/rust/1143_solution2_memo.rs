impl Solution {
    pub fn longest_common_subsequence(text1: String, text2: String) -> i32 {
        let (a, b) = (text1.as_bytes(), text2.as_bytes());
        let (n, m) = (a.len(), b.len());
        let mut dp = vec![vec![-1; m + 1]; n + 1];
        Self::solve(n, m, a, b, &mut dp)
    }

    fn solve(i: usize, j: usize, a: &[u8], b: &[u8], dp: &mut Vec<Vec<i32>>) -> i32 {
        if i == 0 || j == 0 {
            return 0; // one string is empty
        }
        if dp[i][j] != -1 {
            return dp[i][j];
        }

        dp[i][j] = if a[i - 1] == b[j - 1] {
            1 + Self::solve(i - 1, j - 1, a, b, dp)
        } else {
            Self::solve(i - 1, j, a, b, dp).max(Self::solve(i, j - 1, a, b, dp))
        };
        dp[i][j]
    }
}
