struct Solution;

impl Solution {
    fn generate_parenthesis(n: i32) -> Vec<String> {
        let mut res = Vec::new();
        Self::build(n, 0, 0, String::new(), &mut res);
        res
    }

    fn build(n: i32, opened: i32, closed: i32, cur: String, res: &mut Vec<String>) {
        if closed == n {
            // implies opened == n too
            res.push(cur);
            return;
        }
        if opened < n {
            Self::build(n, opened + 1, closed, format!("{cur}("), res);
        }
        if closed < opened {
            Self::build(n, opened, closed + 1, format!("{cur})"), res);
        }
    }
}
