impl Solution {
    pub fn count_substrings(s: String) -> i32 {
        let b = s.as_bytes();
        let n = b.len();
        let mut count = 0;
        let mut dp = vec![vec![false; n]; n];

        for i in 0..n {
            dp[i][i] = true;
            count += 1;
        }

        for len in 2..=n {
            for i in 0..=n - len {
                let j = i + len - 1;

                if b[i] == b[j] && (len == 2 || dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    count += 1;
                }
            }
        }

        count
    }
}
