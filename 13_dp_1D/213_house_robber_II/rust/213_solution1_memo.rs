impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n == 1 {
            return nums[0];
        }

        let mut memo = vec![-1; n];
        let skip_last = Self::max_loot(n as i32 - 2, 0, &nums, &mut memo);

        memo.fill(-1); // reset: different subproblem
        let skip_first = Self::max_loot(n as i32 - 1, 1, &nums, &mut memo);

        skip_last.max(skip_first)
    }

    // idx is i32 so idx - 2 can drop below start without underflow
    fn max_loot(idx: i32, start: i32, nums: &[i32], memo: &mut Vec<i32>) -> i32 {
        if idx < start {
            return 0;
        }
        let i = idx as usize;
        if memo[i] != -1 {
            return memo[i];
        }
        memo[i] = Self::max_loot(idx - 1, start, nums, memo)
            .max(Self::max_loot(idx - 2, start, nums, memo) + nums[i]);
        memo[i]
    }
}
