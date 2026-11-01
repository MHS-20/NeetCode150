impl Solution {
    pub fn check_valid_string(s: String) -> bool {
        let (mut open, mut star) = (Vec::new(), Vec::new()); // indices of unmatched '(' and '*'

        for (i, c) in s.bytes().enumerate() {
            match c {
                b'(' => open.push(i),
                b'*' => star.push(i),
                _ => {
                    if open.pop().is_none() && star.pop().is_none() {
                        return false;
                    }
                }
            }
        }

        // each leftover '(' needs a later '*' to close it
        while let Some(o) = open.pop() {
            match star.pop() {
                Some(st) if st > o => {}
                _ => return false,
            }
        }
        true
    }
}
