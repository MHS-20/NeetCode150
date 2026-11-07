impl Solution {
    pub fn max_product(nums: Vec<i32>) -> i32 {
        let (mut cur_max, mut cur_min, mut best) = (nums[0], nums[0], nums[0]);

        for &x in &nums[1..] {
            let (a, b) = (cur_max * x, cur_min * x);

            cur_max = x.max(a).max(b);
            cur_min = x.min(a).min(b);
            best = best.max(cur_max);
        }
        best
    }
}
