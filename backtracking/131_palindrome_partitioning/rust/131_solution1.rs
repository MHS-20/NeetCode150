impl Solution {
    pub fn partition(s: String) -> Vec<Vec<String>> {
        let mut result = Vec::new();
        let mut path = Vec::new();
        Self::backtrack(s.as_bytes(), 0, &mut path, &mut result);
        result
    }

    fn backtrack(s: &[u8], start: usize, path: &mut Vec<String>, result: &mut Vec<Vec<String>>) {
        if start == s.len() {
            result.push(path.clone());
            return;
        }
        for i in start..s.len() {
            if !Self::is_palindrome(s, start, i) {
                continue;
            }
            // s is lowercase ASCII, so any byte slice is valid UTF-8
            path.push(String::from_utf8(s[start..=i].to_vec()).unwrap());
            Self::backtrack(s, i + 1, path, result);
            path.pop();
        }
    }

    fn is_palindrome(s: &[u8], mut l: usize, mut r: usize) -> bool {
        while l < r {
            if s[l] != s[r] {
                return false;
            }
            l += 1;
            r -= 1;
        }
        true
    }
}
