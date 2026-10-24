impl Solution {
    pub fn subsets(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut result = Vec::with_capacity(1 << nums.len());
        let mut cur = Vec::with_capacity(nums.len());
        Self::backtrack(&nums, 0, &mut cur, &mut result);
        result
    }

    fn backtrack(nums: &[i32], idx: usize, cur: &mut Vec<i32>, result: &mut Vec<Vec<i32>>) {
        if idx == nums.len() {
            result.push(cur.clone());
            return;
        }
        // include nums[idx]
        cur.push(nums[idx]);
        Self::backtrack(nums, idx + 1, cur, result);
        cur.pop(); // undo

        // skip nums[idx]
        Self::backtrack(nums, idx + 1, cur, result);
    }
}
