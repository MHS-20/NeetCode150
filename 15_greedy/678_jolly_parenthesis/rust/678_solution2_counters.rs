impl Solution {
    // hi is the count if every * is a '('. If even that drops below 0, there's an
    // unmatched ')' no matter what. lo is the count if every * is a ')'. Clamping
    // it to 0 throws away choices that would close more than is open.
    pub fn check_valid_string(s: String) -> bool {
        let (mut lo, mut hi) = (0, 0); // min and max possible number of open '('

        for c in s.bytes() {
            match c {
                b'(' => {
                    lo += 1;
                    hi += 1;
                }
                b')' => {
                    lo -= 1;
                    hi -= 1;
                }
                _ => {
                    // '*' could be ')' or '('
                    lo -= 1;
                    hi += 1;
                }
            }

            if hi < 0 {
                return false; // too many ')', even with every '*' as '('
            }
            lo = lo.max(0); // the count can't go negative, so drop those choices
        }

        lo == 0 // some choice of '*' leaves zero open
    }
}
