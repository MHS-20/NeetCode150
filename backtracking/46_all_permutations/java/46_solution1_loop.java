import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(nums.clone(), result, 0);
        return result;
    }

    private void backtrack(int[] cur, List<List<Integer>> result, int idx) {
        if (idx == cur.length) {
            List<Integer> perm = new ArrayList<>(cur.length);
            for (int x : cur) {
                perm.add(x);
            }
            result.add(perm);
            return;
        }

        for (int i = idx; i < cur.length; i++) {
            swap(cur, idx, i);
            backtrack(cur, result, idx + 1);
            swap(cur, idx, i);
        }
    }

    private void swap(int[] a, int i, int j) {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}
