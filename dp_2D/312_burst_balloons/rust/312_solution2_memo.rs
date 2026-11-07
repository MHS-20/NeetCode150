impl Solution {
    pub fn max_coins(nums: Vec<i32>) -> i32 {
        let mut a = vec![1]; // pad: [1, nums..., 1]
        a.extend(&nums);
        a.push(1);

        let n = a.len();
        let mut dp = vec![vec![-1; n]; n];
        Self::f(0, n - 1, &a, &mut dp)
    }

    fn f(l: usize, r: usize, a: &[i32], dp: &mut Vec<Vec<i32>>) -> i32 {
        if r - l < 2 {
            return 0; // nothing strictly between l and r
        }
        if dp[l][r] != -1 {
            return dp[l][r];
        }

        let mut best = 0;
        for k in l + 1..r {
            // k = last balloon burst in (l, r)
            let coins = a[l] * a[k] * a[r] + Self::f(l, k, a, dp) + Self::f(k, r, a, dp);
            best = best.max(coins);
        }
        dp[l][r] = best;
        best
    }
}
