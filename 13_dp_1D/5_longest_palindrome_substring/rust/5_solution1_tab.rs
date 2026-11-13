impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        let b = s.as_bytes();
        let n = b.len();
        let mut memo = vec![vec![false; n]; n];
        let (mut best_start, mut best_len) = (0, 0);

        for i in (0..n).rev() {
            for j in i..n {
                if b[i] == b[j] && (j - i < 2 || memo[i + 1][j - 1]) {
                    memo[i][j] = true;
                    if j - i + 1 > best_len {
                        best_len = j - i + 1;
                        best_start = i;
                    }
                }
            }
        }

        s[best_start..best_start + best_len].to_string()
    }
}
