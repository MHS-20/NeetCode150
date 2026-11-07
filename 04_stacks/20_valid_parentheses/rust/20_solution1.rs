struct Solution;

impl Solution {
    fn is_valid(s: String) -> bool {
        let mut expected: Vec<char> = Vec::new(); // closing brackets we still owe

        for c in s.chars() {
            match c {
                '(' => expected.push(')'),
                '[' => expected.push(']'),
                '{' => expected.push('}'),
                _ => {
                    if expected.pop() != Some(c) {
                        return false;
                    }
                }
            }
        }
        expected.is_empty()
    }
}
