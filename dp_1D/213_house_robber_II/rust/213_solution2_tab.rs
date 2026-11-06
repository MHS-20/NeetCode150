impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n == 1 {
            return nums[0];
        }

        Self::rob_range(&nums, 0, n - 2) // exclude the last house
            .max(Self::rob_range(&nums, 1, n - 1)) // exclude the first house
    }

    // Max loot from houses start..end (inclusive), in a straight line
    fn rob_range(nums: &[i32], start: usize, end: usize) -> i32 {
        let len = end - start + 1;
        if len == 1 {
            return nums[start];
        }

        let mut dp = vec![0; len];
        dp[0] = nums[start];
        dp[1] = nums[start].max(nums[start + 1]);

        for i in 2..len {
            dp[i] = dp[i - 1] // skip this house
                .max(dp[i - 2] + nums[start + i]); // rob this house
        }
        dp[len - 1]
    }
}
