impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        let (a, b) = (word1.as_bytes(), word2.as_bytes());
        let mut dp = vec![vec![-1; b.len() + 1]; a.len() + 1];
        Self::f(a.len(), b.len(), a, b, &mut dp)
    }

    fn f(i: usize, j: usize, a: &[u8], b: &[u8], dp: &mut Vec<Vec<i32>>) -> i32 {
        if i == 0 {
            return j as i32; // insert the remaining j chars
        }
        if j == 0 {
            return i as i32; // delete the remaining i chars
        }
        if dp[i][j] != -1 {
            return dp[i][j];
        }

        dp[i][j] = if a[i - 1] == b[j - 1] {
            Self::f(i - 1, j - 1, a, b, dp) // free match
        } else {
            let del = Self::f(i - 1, j, a, b, dp);
            let ins = Self::f(i, j - 1, a, b, dp);
            let rep = Self::f(i - 1, j - 1, a, b, dp);
            1 + del.min(ins).min(rep)
        };
        dp[i][j]
    }
}
