const MAPPING: [&str; 10] = ["", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"];

impl Solution {
    pub fn letter_combinations(digits: String) -> Vec<String> {
        let mut result = Vec::new();
        if digits.is_empty() {
            return result;
        }
        let mut cur = String::with_capacity(digits.len());
        Self::backtrack(digits.as_bytes(), 0, &mut cur, &mut result);
        result
    }

    fn backtrack(digits: &[u8], idx: usize, cur: &mut String, result: &mut Vec<String>) {
        if idx == digits.len() {
            result.push(cur.clone());
            return;
        }
        for ch in MAPPING[(digits[idx] - b'0') as usize].chars() {
            cur.push(ch); // choose
            Self::backtrack(digits, idx + 1, cur, result);
            cur.pop(); // un-choose
        }
    }
}
