use std::collections::HashSet;

impl Solution {
    pub fn word_break(s: String, word_dict: Vec<String>) -> bool {
        let n = s.len();
        let words: HashSet<&str> = word_dict.iter().map(|w| w.as_str()).collect();
        let mut dp = vec![false; n + 1];
        dp[0] = true; // empty prefix is segmentable

        for i in 1..=n {
            for j in 0..i {
                if dp[j] && words.contains(&s[j..i]) {
                    dp[i] = true;
                    break; // one valid split is enough
                }
            }
        }
        dp[n]
    }
}
