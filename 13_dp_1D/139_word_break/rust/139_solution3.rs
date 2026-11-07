impl Solution {
    pub fn word_break(s: String, word_dict: Vec<String>) -> bool {
        let n = s.len();
        let mut dp = vec![false; n + 1];
        dp[0] = true;

        for i in 1..=n {
            for w in &word_dict {
                let len = w.len();
                // Does word w end exactly at position i?
                if len <= i && dp[i - len] && &s[i - len..i] == w {
                    dp[i] = true;
                    break;
                }
            }
        }
        dp[n]
    }
}
