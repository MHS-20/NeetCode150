impl Solution {
    pub fn is_interleave(s1: String, s2: String, s3: String) -> bool {
        let (a, b, c) = (s1.as_bytes(), s2.as_bytes(), s3.as_bytes());
        let (n, m) = (a.len(), b.len());
        if n + m != c.len() {
            return false;
        }

        let mut dp = vec![vec![false; m + 1]; n + 1];
        dp[0][0] = true; // empty + empty = empty

        for i in 0..=n {
            for j in 0..=m {
                if i == 0 && j == 0 {
                    continue;
                }
                let k = i + j - 1; // last char of s3 prefix
                let from_s1 = i > 0 && dp[i - 1][j] && a[i - 1] == c[k];
                let from_s2 = j > 0 && dp[i][j - 1] && b[j - 1] == c[k];
                dp[i][j] = from_s1 || from_s2;
            }
        }
        dp[n][m]
    }
}
