impl Solution {
    pub fn permute(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut result = Vec::new();
        Self::backtrack(&mut nums, &mut result, 0, 0);
        result
    }

    fn backtrack(nums: &mut Vec<i32>, result: &mut Vec<Vec<i32>>, idx: usize, i: usize) {
        if idx == nums.len() {
            result.push(nums.clone());
            return;
        }
        if i == nums.len() {
            return;
        }

        // choose nums[i] for position idx, then fix the next position
        nums.swap(idx, i);
        Self::backtrack(nums, result, idx + 1, idx + 1);
        nums.swap(idx, i); // undo

        // try the next candidate for the same position
        Self::backtrack(nums, result, idx, i + 1);
    }
}
