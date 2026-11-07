impl Solution {
    pub fn change(amount: i32, coins: Vec<i32>) -> i32 {
        let mut dp = vec![vec![-1i64; amount as usize + 1]; coins.len()];
        Self::f(0, amount as usize, &coins, &mut dp) as i32
    }

    fn f(i: usize, x: usize, coins: &[i32], dp: &mut Vec<Vec<i64>>) -> i64 {
        if x == 0 {
            return 1; // made the amount
        }
        if i == coins.len() {
            return 0; // out of coins
        }
        if dp[i][x] != -1 {
            return dp[i][x];
        }

        let skip = Self::f(i + 1, x, coins, dp); // never use coin i again
        let c = coins[i] as usize;
        let take = if c <= x {
            Self::f(i, x - c, coins, dp) // use coin i, stay at i (reuse allowed)
        } else {
            0
        };

        // keep within u32 range so -1 stays a free sentinel and nothing overflows
        dp[i][x] = (skip + take) & 0xFFFF_FFFF;
        dp[i][x]
    }
}
