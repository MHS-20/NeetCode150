impl Solution {
    pub fn min_cost_climbing_stairs(cost: Vec<i32>) -> i32 {
        let mut memo = vec![-1; cost.len() + 1];
        Self::costs(cost.len(), &cost, &mut memo)
    }

    fn costs(i: usize, cost: &[i32], memo: &mut Vec<i32>) -> i32 {
        if i <= 1 {
            return 0; // start on step 0 or 1 for free
        }
        if memo[i] != -1 {
            return memo[i];
        }
        memo[i] = (Self::costs(i - 1, cost, memo) + cost[i - 1])
            .min(Self::costs(i - 2, cost, memo) + cost[i - 2]);
        memo[i]
    }
}
