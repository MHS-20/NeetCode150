impl Solution {
    pub fn subsets_with_dup(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut result = Vec::new();
        let mut cur = Vec::with_capacity(nums.len());
        nums.sort_unstable();
        Self::backtrack(&nums, 0, &mut cur, &mut result);
        result
    }

    fn backtrack(nums: &[i32], idx: usize, cur: &mut Vec<i32>, result: &mut Vec<Vec<i32>>) {
        if idx == nums.len() {
            result.push(cur.clone());
            return;
        }

        cur.push(nums[idx]);
        Self::backtrack(nums, idx + 1, cur, result);
        cur.pop();

        let mut i = idx + 1;
        while i < nums.len() && nums[idx] == nums[i] {
            i += 1;
        }

        Self::backtrack(nums, i, cur, result);
    }
}
