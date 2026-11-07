impl Solution {
    pub fn max_chunks_to_sorted(arr: Vec<i32>) -> i32 {
        let mut st: Vec<i32> = Vec::new();

        for n in arr {
            match st.last() {
                Some(&top) if n <= top => {
                    let mx = st.pop().unwrap();
                    while st.last().is_some_and(|&t| n <= t) {
                        st.pop();
                    }
                    st.push(mx);
                }
                _ => st.push(n),
            }
        }

        st.len() as i32
    }
}
