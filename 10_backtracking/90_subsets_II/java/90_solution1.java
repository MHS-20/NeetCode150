import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<List<Integer>> subsetsWithDup(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        Arrays.sort(nums);
        backtrack(nums, 0, new ArrayList<>(), result);
        return result;
    }

    private void backtrack(int[] nums, int idx, List<Integer> cur, List<List<Integer>> result) {
        if (idx == nums.length) {
            result.add(new ArrayList<>(cur));
            return;
        }

        cur.add(nums[idx]);
        backtrack(nums, idx + 1, cur, result);
        cur.remove(cur.size() - 1);

        int i = idx + 1;
        while (i < nums.length && nums[idx] == nums[i]) {
            i++;
        }

        backtrack(nums, i, cur, result);
    }
}
