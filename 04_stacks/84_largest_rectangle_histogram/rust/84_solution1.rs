struct Solution;

impl Solution {
    fn largest_rectangle_area(heights: Vec<i32>) -> i32 {
        let n = heights.len();
        let mut st: Vec<usize> = Vec::new(); // indices of increasing heights
        let mut best = 0;

        for i in 0..=n {
            let h = if i < n { heights[i] } else { 0 }; // sentinel flushes the stack
            while let Some(&top) = st.last() {
                if heights[top] <= h {
                    break;
                }
                st.pop();
                let prev = st.last().map_or(-1, |&p| p as i32);
                best = best.max(heights[top] * (i as i32 - prev - 1));
            }
            st.push(i);
        }
        best
    }
}
