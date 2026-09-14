struct Solution;

impl Solution {
    fn is_palindrome(s: String) -> bool {
        let chars: Vec<char> = s.chars().collect();
        let mut left = 0i32;
        let mut right = chars.len() as i32 - 1;

        while left < right {
            while left < right && !chars[left as usize].is_alphanumeric() {
                left += 1;
            }
            while left < right && !chars[right as usize].is_alphanumeric() {
                right -= 1;
            }

            if chars[left as usize].to_ascii_lowercase() != chars[right as usize].to_ascii_lowercase() {
                return false;
            }

            left += 1;
            right -= 1;
        }

        true
    }
}
