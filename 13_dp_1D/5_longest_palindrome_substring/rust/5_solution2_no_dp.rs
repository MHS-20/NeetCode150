impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        let b = s.as_bytes();
        let (mut best_start, mut best_len) = (0, 0);

        for i in 0..b.len() {
            let odd_len = Self::expand(b, i as i32, i as i32); // center on a character: "aba"
            let even_len = Self::expand(b, i as i32, i as i32 + 1); // center between two characters: "abba"
            let len = odd_len.max(even_len);

            if len > best_len {
                best_len = len;
                best_start = i - (len - 1) / 2;
            }
        }
        s[best_start..best_start + best_len].to_string()
    }

    // Grow outward from the center (left, right) while the ends match.
    // Returns the length of the palindrome found.
    // left is i32 so it can step below 0 without underflow
    fn expand(b: &[u8], mut left: i32, mut right: i32) -> usize {
        while left >= 0 && (right as usize) < b.len() && b[left as usize] == b[right as usize] {
            left -= 1;
            right += 1;
        }
        (right - left - 1) as usize
    }
}
