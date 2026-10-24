impl Solution {
    pub fn subsets(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut result = Vec::with_capacity(1 << nums.len());
        let mut cur = Vec::with_capacity(nums.len());
        Self::backtrack(&nums, 0, &mut cur, &mut result);
        result
    }

    fn backtrack(nums: &[i32], start: usize, cur: &mut Vec<i32>, result: &mut Vec<Vec<i32>>) {
        result.push(cur.clone()); // every path is a valid subset

        for i in start..nums.len() {
            cur.push(nums[i]);
            Self::backtrack(nums, i + 1, cur, result);
            cur.pop(); // undo
        }
    }
}
