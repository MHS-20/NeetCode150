struct Solution;

impl Solution {
    fn trap(height: Vec<i32>) -> i32 {
        if height.is_empty() {
            return 0;
        }

        let mut left = 0usize;
        let mut right = height.len() - 1;
        let mut left_max = height[left];
        let mut right_max = height[right];
        let mut total = 0;

        while left < right {
            if left_max < right_max {
                left += 1;
                left_max = left_max.max(height[left]);
                total += left_max - height[left];
            } else {
                right -= 1;
                right_max = right_max.max(height[right]);
                total += right_max - height[right];
            }
        }

        total
    }
}
