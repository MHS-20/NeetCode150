impl Solution {
    pub fn is_match(s: String, p: String) -> bool {
        let (s, p) = (s.as_bytes(), p.as_bytes());
        let mut dp = vec![vec![None; p.len() + 1]; s.len() + 1]; // None = not computed
        Self::f(s.len(), p.len(), s, p, &mut dp)
    }

    fn matches(s: &[u8], p: &[u8], i: usize, j: usize) -> bool {
        // s[i-1] vs p[j-1]
        p[j - 1] == b'.' || s[i - 1] == p[j - 1]
    }

    fn f(i: usize, j: usize, s: &[u8], p: &[u8], dp: &mut Vec<Vec<Option<bool>>>) -> bool {
        if j == 0 {
            return i == 0; // empty pattern matches only empty s
        }
        if let Some(res) = dp[i][j] {
            return res;
        }

        let res = if p[j - 1] == b'*' {
            // zero copies, or one more copy
            Self::f(i, j - 2, s, p, dp)
                || (i > 0 && Self::matches(s, p, i, j - 1) && Self::f(i - 1, j, s, p, dp))
        } else {
            i > 0 && Self::matches(s, p, i, j) && Self::f(i - 1, j - 1, s, p, dp)
        };

        dp[i][j] = Some(res);
        res
    }
}
