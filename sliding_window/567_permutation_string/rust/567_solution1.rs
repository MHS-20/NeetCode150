struct Solution;

impl Solution {
    fn check_inclusion(s1: String, s2: String) -> bool {
        let (a, b) = (s1.as_bytes(), s2.as_bytes());
        if a.len() > b.len() {
            return false;
        }

        let mut s1freq = [0i32; 26];
        let mut windowfreq = [0i32; 26];
        for i in 0..a.len() {
            s1freq[(a[i] - b'a') as usize] += 1;
            windowfreq[(b[i] - b'a') as usize] += 1;
        }

        let mut matches = (0..26).filter(|&i| s1freq[i] == windowfreq[i]).count();
        if matches == 26 {
            return true;
        }

        let mut left = 0;
        for right in a.len()..b.len() {
            let r = (b[right] - b'a') as usize;
            let l = (b[left] - b'a') as usize;

            // add right char
            if windowfreq[r] == s1freq[r] {
                matches -= 1;
            }
            windowfreq[r] += 1;
            if windowfreq[r] == s1freq[r] {
                matches += 1;
            }

            // remove left char
            if windowfreq[l] == s1freq[l] {
                matches -= 1;
            }
            windowfreq[l] -= 1;
            if windowfreq[l] == s1freq[l] {
                matches += 1;
            }

            left += 1;
            if matches == 26 {
                return true;
            }
        }
        false
    }
}
