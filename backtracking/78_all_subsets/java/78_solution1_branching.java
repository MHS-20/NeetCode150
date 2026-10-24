import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(nums, 0, new ArrayList<>(), result);
        return result;
    }

    private void backtrack(int[] nums, int idx, List<Integer> cur, List<List<Integer>> result) {
        if (idx == nums.length) {
            result.add(new ArrayList<>(cur));
            return;
        }
        // include nums[idx]
        cur.add(nums[idx]);
        backtrack(nums, idx + 1, cur, result);
        cur.remove(cur.size() - 1); // undo

        // skip nums[idx]
        backtrack(nums, idx + 1, cur, result);
    }
}
