use std::collections::HashMap;

impl Solution {
    pub fn is_anagram(s: String, t: String) -> bool {
        // chars() already iterates Unicode scalar values, so this is
        // equivalent to solution2 — Rust needs no extra step here, unlike
        // C++'s byte-oriented std::string.
        if s.chars().count() != t.chars().count() {
            return false;
        }

        let mut counts: HashMap<char, i32> = HashMap::new();
        for c in s.chars() {
            *counts.entry(c).or_insert(0) += 1;
        }

        for c in t.chars() {
            match counts.get_mut(&c) {
                Some(count) if *count > 0 => *count -= 1,
                _ => return false,
            }
        }

        true
    }
}

struct Solution;
