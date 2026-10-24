import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(nums, result, 0, 0);
        return result;
    }

    private void backtrack(int[] nums, List<List<Integer>> result, int idx, int i) {
        if (idx == nums.length) {
            List<Integer> perm = new ArrayList<>(nums.length);
            for (int x : nums) {
                perm.add(x);
            }
            result.add(perm);
            return;
        }
        if (i == nums.length) {
            return;
        }

        // choose nums[i] for position idx, then fix the next position
        swap(nums, idx, i);
        backtrack(nums, result, idx + 1, idx + 1);
        swap(nums, idx, i); // undo

        // try the next candidate for the same position
        backtrack(nums, result, idx, i + 1);
    }

    private void swap(int[] a, int i, int j) {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}
