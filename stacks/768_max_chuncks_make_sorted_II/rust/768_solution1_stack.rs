impl Solution {
    pub fn max_chunks_to_sorted(arr: Vec<i32>) -> i32 {
        let mut st: Vec<i32> = Vec::new(); // max of each chunk, non-decreasing
        for x in arr {
            let mut cur_max = x;
            while let Some(&top) = st.last() {
                if top <= x {
                    break;
                }
                cur_max = cur_max.max(top);
                st.pop();
            }
            st.push(cur_max);
        }
        st.len() as i32
    }
}
