struct Solution;

impl Solution {
    fn eval_rpn(tokens: Vec<String>) -> i32 {
        let mut st: Vec<i32> = Vec::new();

        for s in &tokens {
            if matches!(s.as_str(), "+" | "-" | "*" | "/") {
                let b = st.pop().unwrap();
                let a = st.pop().unwrap();

                st.push(match s.as_str() {
                    "+" => a + b,
                    "-" => a - b,
                    "*" => a * b,
                    _ => a / b,
                });
            } else {
                st.push(s.parse().unwrap());
            }
        }

        *st.last().unwrap()
    }
}
