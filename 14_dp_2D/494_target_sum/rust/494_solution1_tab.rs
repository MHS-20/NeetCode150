impl Solution {
    pub fn find_target_sum_ways(nums: Vec<i32>, target: i32) -> i32 {
        let n = nums.len();
        let tot: i32 = nums.iter().sum();
        if target.abs() > tot {
            return 0;
        }

        let idx = |s: i32| (s + tot) as usize; // shift sums into 0..=2*tot
        let mut dp = vec![vec![0; 2 * tot as usize + 1]; n + 1];
        dp[0][idx(0)] = 1; // 0 numbers used, sum 0

        for i in 1..=n {
            let x = nums[i - 1];
            for s in -tot..=tot {
                let mut ways = 0;
                if s - x >= -tot {
                    ways += dp[i - 1][idx(s - x)]; // added x
                }
                if s + x <= tot {
                    ways += dp[i - 1][idx(s + x)]; // subtracted x
                }
                dp[i][idx(s)] = ways;
            }
        }
        dp[n][idx(target)]
    }
}
