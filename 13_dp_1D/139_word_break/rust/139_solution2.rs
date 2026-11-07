use std::collections::HashSet;

impl Solution {
    pub fn word_break(s: String, word_dict: Vec<String>) -> bool {
        let n = s.len();
        let words: HashSet<&str> = word_dict.iter().map(|w| w.as_str()).collect();
        let max_len = word_dict.iter().map(|w| w.len()).max().unwrap_or(0);

        let mut dp = vec![false; n + 1];
        dp[0] = true;

        for i in 1..=n {
            // A piece longer than max_len can't be a word, so start j no earlier
            // than i - max_len
            for j in i.saturating_sub(max_len)..i {
                if dp[j] && words.contains(&s[j..i]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        dp[n]
    }
}
