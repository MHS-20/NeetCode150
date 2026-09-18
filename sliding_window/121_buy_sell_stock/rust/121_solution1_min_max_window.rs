struct Solution;

impl Solution {
    fn max_profit(prices: Vec<i32>) -> i32 {
        let mut mn = i32::MAX;
        let mut profit = 0;

        for p in prices {
            mn = mn.min(p);
            profit = profit.max(p - mn);
        }

        profit
    }
}
