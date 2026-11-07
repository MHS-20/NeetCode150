use std::collections::HashMap;

struct Solution;

impl Solution {
    fn check_inclusion(s1: String, s2: String) -> bool {
        let (a, b) = (s1.as_bytes(), s2.as_bytes());
        let k = a.len();
        let mut diff: HashMap<u8, i32> = HashMap::new();
        let mut mismatched = 0;

        // shift a letter's diff by delta, keeping `mismatched` in sync
        // (returns the updated count, since the closure holds `mismatched` mutably)
        let mut update = |c: u8, delta: i32| {
            let d = diff.entry(c).or_insert(0);
            if *d == 0 {
                mismatched += 1; // was balanced, about to break
            }
            *d += delta;
            if *d == 0 {
                mismatched -= 1; // now balanced again
            }
            mismatched
        };

        for &c in a {
            update(c, -1);
        }

        for right in 0..b.len() {
            let mut m = update(b[right], 1); // char enters
            if right >= k {
                m = update(b[right - k], -1); // char leaves
            }
            if m == 0 {
                return true;
            }
        }
        false
    }
}
