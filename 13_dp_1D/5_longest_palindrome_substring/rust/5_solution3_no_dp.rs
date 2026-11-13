impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        let b = s.as_bytes();
        let (mut best_start, mut best_len) = (0, 0);

        for i in 0..b.len() {
            // odd-length palindromes, centered on s[i]
            Self::expand(b, i as i32, i as i32, &mut best_start, &mut best_len);
            // even-length palindromes, centered between s[i] and s[i+1]
            Self::expand(b, i as i32, i as i32 + 1, &mut best_start, &mut best_len);
        }

        s[best_start..best_start + best_len].to_string()
    }

    fn expand(b: &[u8], mut l: i32, mut r: i32, best_start: &mut usize, best_len: &mut usize) {
        // bounds first, so s[l] and s[r] are only read when valid
        while l >= 0 && (r as usize) < b.len() && b[l as usize] == b[r as usize] {
            l -= 1;
            r += 1;
        }
        // pointers overshot by one on each side: palindrome is s[l+1 .. r-1]
        let len = (r - l - 1) as usize;
        if len > *best_len {
            *best_len = len;
            *best_start = (l + 1) as usize;
        }
    }
}
