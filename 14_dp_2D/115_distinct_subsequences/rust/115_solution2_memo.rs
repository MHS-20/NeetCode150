impl Solution {
    pub fn num_distinct(s: String, t: String) -> i32 {
        let (s, t) = (s.as_bytes(), t.as_bytes());
        let mut dp = vec![vec![None; t.len() + 1]; s.len() + 1]; // None = not computed
        Self::f(s.len(), t.len(), s, t, &mut dp) as i32
    }

    fn f(i: usize, j: usize, s: &[u8], t: &[u8], dp: &mut Vec<Vec<Option<u32>>>) -> u32 {
        if j == 0 {
            return 1; // t fully matched
        }
        if i == 0 {
            return 0; // s ran out first
        }
        if let Some(ways) = dp[i][j] {
            return ways;
        }

        let mut ways = Self::f(i - 1, j, s, t, dp); // skip s[i-1]
        if s[i - 1] == t[j - 1] {
            // pick it; wrapping: intermediates may overflow
            ways = ways.wrapping_add(Self::f(i - 1, j - 1, s, t, dp));
        }

        dp[i][j] = Some(ways);
        ways
    }
}
