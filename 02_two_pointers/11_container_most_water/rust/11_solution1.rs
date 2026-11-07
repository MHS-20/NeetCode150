struct Solution;

impl Solution {
    fn max_area(height: Vec<i32>) -> i32 {
        let mut left = 0usize;
        let mut right = height.len() - 1;
        let mut mx = 0;

        while left < right {
            let width = (right - left) as i32;
            let h = height[left].min(height[right]);
            mx = mx.max(h * width);

            if height[left] > height[right] {
                right -= 1;
            } else {
                left += 1;
            }
        }

        mx
    }
}
