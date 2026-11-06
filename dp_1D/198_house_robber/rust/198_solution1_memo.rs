impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        let mut memo = vec![-1; nums.len()];
        Self::max_loot(nums.len() - 1, &nums, &mut memo)
    }

    fn max_loot(idx: usize, nums: &[i32], memo: &mut Vec<i32>) -> i32 {
        if idx == 0 {
            return nums[0];
        }
        if idx == 1 {
            return nums[0].max(nums[1]);
        }

        if memo[idx] != -1 {
            return memo[idx];
        }

        memo[idx] = Self::max_loot(idx - 1, nums, memo) // skip this house
            .max(Self::max_loot(idx - 2, nums, memo) + nums[idx]); // rob this house
        memo[idx]
    }
}
