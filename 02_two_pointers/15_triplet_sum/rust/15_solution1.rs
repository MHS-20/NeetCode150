struct Solution;

impl Solution {
    fn three_sum(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
        nums.sort();
        let mut result = Vec::new();
        let n = nums.len();

        for idx in 0..n {
            if idx > 0 && nums[idx] == nums[idx - 1] {
                continue;
            }

            let mut left = idx + 1;
            let mut right = n - 1;

            while left < right {
                let total = nums[idx] + nums[left] + nums[right];

                if total == 0 {
                    result.push(vec![nums[idx], nums[left], nums[right]]);
                    left += 1;
                    right -= 1;
                    while left < right && nums[left] == nums[left - 1] {
                        left += 1;
                    }
                    while left < right && nums[right] == nums[right + 1] {
                        right -= 1;
                    }
                } else if total > 0 {
                    right -= 1;
                } else {
                    left += 1;
                }
            }
        }

        result
    }
}
