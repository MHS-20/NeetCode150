import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        Arrays.sort(candidates);
        backtrack(candidates, 0, 0, target, new ArrayList<>(), result);
        return result;
    }

    private void backtrack(int[] candidates, int idx, int sum, int target,
                           List<Integer> cur, List<List<Integer>> result) {
        if (sum == target) {
            result.add(new ArrayList<>(cur));
            return;
        }

        if (sum > target || idx == candidates.length) {
            return;
        }

        cur.add(candidates[idx]);
        backtrack(candidates, idx + 1, sum + candidates[idx], target, cur, result);
        cur.remove(cur.size() - 1);

        int i = idx + 1;
        while (i < candidates.length && candidates[i] == candidates[idx]) {
            i++;
        }
        backtrack(candidates, i, sum, target, cur, result);
    }
}
