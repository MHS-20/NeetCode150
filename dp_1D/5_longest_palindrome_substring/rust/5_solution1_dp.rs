impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        let b = s.as_bytes();
        let n = b.len();
        let mut dp = vec![vec![false; n]; n];
        let (mut best_start, mut best_len) = (0, 1);

        // Every single character is a palindrome
        for i in 0..n {
            dp[i][i] = true;
        }

        // Fill by increasing substring length
        for len in 2..=n {
            for i in 0..=n - len {
                let j = i + len - 1;

                if b[i] == b[j] && (len == 2 || dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    if len > best_len {
                        best_start = i;
                        best_len = len;
                    }
                }
            }
        }
        s[best_start..best_start + best_len].to_string()
    }
}
