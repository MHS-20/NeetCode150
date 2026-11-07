impl Solution {
    pub fn find_target_sum_ways(nums: Vec<i32>, target: i32) -> i32 {
        let tot: i32 = nums.iter().sum();
        if target.abs() > tot {
            return 0;
        }

        // dp[i][sum + tot], -1 = not computed
        let mut dp = vec![vec![-1; 2 * tot as usize + 1]; nums.len()];
        Self::f(0, 0, &nums, target, tot, &mut dp)
    }

    // Ways to reach target using nums[i..], given the running sum so far
    fn f(i: usize, sum: i32, nums: &[i32], target: i32, tot: i32, dp: &mut Vec<Vec<i32>>) -> i32 {
        if i == nums.len() {
            return if sum == target { 1 } else { 0 };
        }
        let k = (sum + tot) as usize;
        if dp[i][k] != -1 {
            return dp[i][k];
        }

        let add = Self::f(i + 1, sum + nums[i], nums, target, tot, dp); // +nums[i]
        let sub = Self::f(i + 1, sum - nums[i], nums, target, tot, dp); // -nums[i]
        dp[i][k] = add + sub;
        dp[i][k]
    }
}
