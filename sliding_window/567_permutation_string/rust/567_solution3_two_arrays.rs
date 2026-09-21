struct Solution;

impl Solution {
    fn check_inclusion(s1: String, s2: String) -> bool {
        let (a, b) = (s1.as_bytes(), s2.as_bytes());
        let k = a.len();
        let mut freq = [0i32; 26];
        let mut wfreq = [0i32; 26];
        for &c in a {
            freq[(c - b'a') as usize] += 1;
        }

        // matches = number of the 26 letters whose window count equals freq
        // empty window: letters absent from s1 already match
        let mut matches = freq.iter().filter(|&&f| f == 0).count();

        // change the window count of a letter by delta, keeping `matches` in sync
        // (returns the updated count, since the closure holds `matches` mutably)
        let mut update = |ch: u8, delta: i32| {
            let c = (ch - b'a') as usize;
            if wfreq[c] == freq[c] {
                matches -= 1; // was matching, about to change
            }
            wfreq[c] += delta;
            if wfreq[c] == freq[c] {
                matches += 1; // matches now
            }
            matches
        };

        for right in 0..b.len() {
            let mut m = update(b[right], 1); // char enters
            if right >= k {
                m = update(b[right - k], -1); // char leaves
            }
            if m == 26 {
                return true;
            }
        }
        false
    }
}
