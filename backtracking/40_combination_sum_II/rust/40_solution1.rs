impl Solution {
    pub fn combination_sum2(mut candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
        let mut result = Vec::new();
        let mut cur = Vec::new();
        candidates.sort_unstable();
        Self::backtrack(&candidates, 0, 0, target, &mut cur, &mut result);
        result
    }

    fn backtrack(
        candidates: &[i32],
        idx: usize,
        sum: i32,
        target: i32,
        cur: &mut Vec<i32>,
        result: &mut Vec<Vec<i32>>,
    ) {
        if sum == target {
            result.push(cur.clone());
            return;
        }

        if sum > target || idx == candidates.len() {
            return;
        }

        cur.push(candidates[idx]);
        Self::backtrack(candidates, idx + 1, sum + candidates[idx], target, cur, result);
        cur.pop();

        let mut i = idx + 1;
        while i < candidates.len() && candidates[i] == candidates[idx] {
            i += 1;
        }
        Self::backtrack(candidates, i, sum, target, cur, result);
    }
}
