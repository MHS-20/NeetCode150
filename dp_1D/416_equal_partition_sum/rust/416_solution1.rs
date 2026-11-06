impl Solution {
    pub fn can_partition(nums: Vec<i32>) -> bool {
        let total: i32 = nums.iter().sum();
        if total % 2 != 0 {
            return false;
        }
        let target = (total / 2) as usize;

        let mut dp = vec![false; target + 1];
        dp[0] = true;

        for &x in &nums {
            let x = x as usize;
            // Go backward so each number is used at most once
            for s in (x..=target).rev() {
                if dp[s - x] {
                    dp[s] = true;
                }
            }
        }
        dp[target]
    }
}
