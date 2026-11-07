impl Solution {
    pub fn max_coins(nums: Vec<i32>) -> i32 {
        let mut a = vec![1]; // pad: [1, nums..., 1]
        a.extend(&nums);
        a.push(1);

        let n = a.len();
        let mut dp = vec![vec![0; n]; n]; // len < 2 → 0 already

        for len in 2..n {
            // distance between walls
            for l in 0..n - len {
                let r = l + len;
                for k in l + 1..r {
                    dp[l][r] = dp[l][r].max(dp[l][k] + dp[k][r] + a[l] * a[k] * a[r]);
                }
            }
        }
        dp[0][n - 1]
    }
}
