impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        let b = s.as_bytes();
        let n = b.len();
        let mut memo = vec![vec![None; n]; n]; // None unknown
        let (mut best_start, mut best_len) = (0, 0);

        for i in 0..n {
            for j in i..n {
                if j - i + 1 > best_len && Self::is_pal(b, i, j, &mut memo) {
                    best_len = j - i + 1;
                    best_start = i;
                }
            }
        }
        s[best_start..best_start + best_len].to_string()
    }

    fn is_pal(b: &[u8], i: usize, j: usize, memo: &mut Vec<Vec<Option<bool>>>) -> bool {
        if i >= j {
            return true; // length 0 or 1
        }
        if let Some(v) = memo[i][j] {
            return v;
        }
        let v = b[i] == b[j] && Self::is_pal(b, i + 1, j - 1, memo);
        memo[i][j] = Some(v);
        v
    }
}
