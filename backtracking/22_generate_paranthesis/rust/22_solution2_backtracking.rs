struct Solution;

impl Solution {
    fn generate_parenthesis(n: i32) -> Vec<String> {
        let mut res = Vec::new();
        let mut cur = String::with_capacity(2 * n as usize);
        Self::backtrack(n, 0, 0, &mut cur, &mut res);
        res
    }

    fn backtrack(n: i32, opened: i32, closed: i32, cur: &mut String, res: &mut Vec<String>) {
        if closed == n {
            // implies opened == n too
            res.push(cur.clone()); // copies once, only for finished answers
            return;
        }

        if opened < n {
            cur.push('('); // choose
            Self::backtrack(n, opened + 1, closed, cur, res); // explore
            cur.pop(); // undo
        }

        if closed < opened {
            cur.push(')');
            Self::backtrack(n, opened, closed + 1, cur, res);
            cur.pop();
        }
    }
}
