use std::collections::HashMap;

struct Solution;

impl Solution {
    fn check_inclusion(s1: String, s2: String) -> bool {
        let (a, b) = (s1.as_bytes(), s2.as_bytes());
        let k = a.len();
        let mut freq: HashMap<u8, i32> = HashMap::new();
        let mut wfreq: HashMap<u8, i32> = HashMap::new();
        for &c in a {
            *freq.entry(c).or_insert(0) += 1;
        }

        let need = freq.len(); // distinct letters in s1, fixed from here on
        let mut matches = 0; // letters of s1 whose window count equals freq

        // change the window count of c by delta, keeping `matches` in sync
        // (returns the updated count, since the closure holds `matches` mutably)
        let mut update = |c: u8, delta: i32| {
            if let Some(&target) = freq.get(&c) {
                let count = wfreq.entry(c).or_insert(0);
                if *count == target {
                    matches -= 1; // was matching, about to change
                }
                *count += delta;
                if *count == target {
                    matches += 1; // matches now
                }
            } // else: not in s1, irrelevant
            matches
        };

        for right in 0..b.len() {
            let mut m = update(b[right], 1); // char enters
            if right >= k {
                m = update(b[right - k], -1); // char leaves
            }
            if m == need {
                return true;
            }
        }
        false
    }
}
