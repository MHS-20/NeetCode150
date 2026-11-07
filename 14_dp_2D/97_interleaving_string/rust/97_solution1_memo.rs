impl Solution {
    pub fn is_interleave(s1: String, s2: String, s3: String) -> bool {
        let (a, b, c) = (s1.as_bytes(), s2.as_bytes(), s3.as_bytes());
        if a.len() + b.len() != c.len() {
            return false;
        }

        let mut dp = vec![vec![None; b.len() + 1]; a.len() + 1]; // None = not computed
        Self::f(0, 0, a, b, c, &mut dp)
    }

    fn f(i: usize, j: usize, a: &[u8], b: &[u8], c: &[u8], dp: &mut Vec<Vec<Option<bool>>>) -> bool {
        if i == a.len() && j == b.len() {
            return true; // used everything
        }
        if let Some(res) = dp[i][j] {
            return res;
        }

        let k = i + j; // position in s3
        let mut res = false;
        if i < a.len() && a[i] == c[k] {
            res = Self::f(i + 1, j, a, b, c, dp); // take from s1
        }
        if !res && j < b.len() && b[j] == c[k] {
            res = Self::f(i, j + 1, a, b, c, dp); // take from s2
        }

        dp[i][j] = Some(res);
        res
    }
}
