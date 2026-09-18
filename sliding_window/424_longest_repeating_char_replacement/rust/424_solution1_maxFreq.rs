use std::collections::HashMap;

struct Solution;

impl Solution {
    fn character_replacement(s: String, k: i32) -> i32 {
        let bytes = s.as_bytes();
        let mut reps: HashMap<u8, i32> = HashMap::new();
        let mut left: i32 = 0;
        let mut max_len = k;
        let mut max_freq = 0;

        for right in 0..bytes.len() {
            let c = bytes[right];
            let count = reps.entry(c).or_insert(0);
            *count += 1;
            max_freq = max_freq.max(*count);

            if right as i32 - left - max_freq >= k {
                *reps.get_mut(&bytes[left as usize]).unwrap() -= 1;
                left += 1;
            }

            max_len = max_len.max(right as i32 - left + 1);
        }

        max_len
    }
}
