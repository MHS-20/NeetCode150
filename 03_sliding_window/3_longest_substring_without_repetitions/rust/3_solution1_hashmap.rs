use std::collections::HashMap;

struct Solution;

impl Solution {
    fn length_of_longest_substring(s: String) -> i32 {
        let bytes = s.as_bytes();
        let mut last_seen: HashMap<u8, i32> = HashMap::new();
        let mut max_len = 0;
        let mut left: i32 = 0;

        for right in 0..bytes.len() {
            let c = bytes[right];

            if let Some(&idx) = last_seen.get(&c) {
                if idx >= left {
                    left = idx + 1;
                }
            }

            last_seen.insert(c, right as i32);
            max_len = max_len.max(right as i32 - left + 1);
        }

        max_len
    }
}
