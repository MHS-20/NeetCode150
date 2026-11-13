impl Solution {
    pub fn count_substrings(s: String) -> i32 {
        let b = s.as_bytes();
        let n = b.len();
        let mut count = 0;
        let mut memo = vec![vec![false; n]; n];

        for i in (0..n).rev() {
            for j in i..n {
                if b[i] == b[j] && (j - i < 2 || memo[i + 1][j - 1]) {
                    memo[i][j] = true;
                    count += 1;
                }
            }
        }

        count
    }
}
