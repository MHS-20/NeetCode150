struct Solution;

impl Solution {
    fn daily_temperatures(temps: Vec<i32>) -> Vec<i32> {
        let mut res = vec![0; temps.len()];
        let mut st: Vec<usize> = Vec::new(); // indices with no warmer day yet

        for (i, &t) in temps.iter().enumerate() {
            while let Some(&j) = st.last() {
                if t <= temps[j] {
                    break;
                }
                st.pop();
                res[j] = (i - j) as i32;
            }
            st.push(i);
        }
        res
    }
}
