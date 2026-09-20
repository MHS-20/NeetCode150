struct Solution;

impl Solution {
    fn min_window(s: String, t: String) -> String {
        let (sb, tb) = (s.as_bytes(), t.as_bytes());
        let mut need = [0i32; 128];
        for &c in tb {
            need[c as usize] += 1;
        }
        let mut missing = tb.len();

        let (mut best_start, mut best_len) = (0, usize::MAX);
        let mut left = 0;

        for right in 0..sb.len() {
            let r = sb[right] as usize;
            if need[r] > 0 {
                missing -= 1; // this char was still needed
            }
            need[r] -= 1;

            while missing == 0 {
                // window is valid: try to shrink
                if right - left + 1 < best_len {
                    best_start = left;
                    best_len = right - left + 1;
                }
                let l = sb[left] as usize;
                need[l] += 1;
                if need[l] > 0 {
                    missing += 1; // we just removed a needed char
                }
                left += 1;
            }
        }

        if best_len == usize::MAX {
            String::new()
        } else {
            s[best_start..best_start + best_len].to_string()
        }
    }
}
