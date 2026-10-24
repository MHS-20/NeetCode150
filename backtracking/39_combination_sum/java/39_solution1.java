import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(result, new ArrayList<>(), 0, candidates, target, 0);
        return result;
    }

    private void backtrack(List<List<Integer>> result, List<Integer> cur, int idx,
                           int[] candidates, int target, int sum) {
        if (sum == target) {
            result.add(new ArrayList<>(cur));
            return;
        }
        if (sum > target || idx >= candidates.length) {
            return;
        }

        // include candidates[idx], stay on idx (can reuse it)
        cur.add(candidates[idx]);
        backtrack(result, cur, idx, candidates, target, sum + candidates[idx]);
        cur.remove(cur.size() - 1);

        // skip candidates[idx] for good, move on
        backtrack(result, cur, idx + 1, candidates, target, sum);
    }
}
