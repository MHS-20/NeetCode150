impl Solution {
    pub fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut result = Vec::new();
        let mut cur = nums.clone();
        Self::backtrack(&mut result, &mut cur, 0);
        result
    }

    fn backtrack(result: &mut Vec<Vec<i32>>, cur: &mut Vec<i32>, idx: usize) {
        if idx == cur.len() {
            result.push(cur.clone());
            return;
        }

        for i in idx..cur.len() {
            cur.swap(idx, i);
            Self::backtrack(result, cur, idx + 1);
            cur.swap(idx, i);
        }
    }
}
