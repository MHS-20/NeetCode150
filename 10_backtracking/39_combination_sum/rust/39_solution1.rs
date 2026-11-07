impl Solution {
    pub fn combination_sum(candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
        let mut result = Vec::new();
        let mut cur = Vec::new();
        Self::backtrack(&mut result, &mut cur, 0, &candidates, target, 0);
        result
    }

    fn backtrack(
        result: &mut Vec<Vec<i32>>,
        cur: &mut Vec<i32>,
        idx: usize,
        candidates: &[i32],
        target: i32,
        sum: i32,
    ) {
        if sum == target {
            result.push(cur.clone());
            return;
        }
        if sum > target || idx >= candidates.len() {
            return;
        }

        // include candidates[idx], stay on idx (can reuse it)
        cur.push(candidates[idx]);
        Self::backtrack(result, cur, idx, candidates, target, sum + candidates[idx]);
        cur.pop();

        // skip candidates[idx] for good, move on
        Self::backtrack(result, cur, idx + 1, candidates, target, sum);
    }
}
