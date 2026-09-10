import java.util.HashSet;
import java.util.Set;

class Solution {
    public boolean containsDuplicate(int[] nums) {
        Set<Integer> tracker = new HashSet<>(nums.length * 2);

        for (int x : nums) {
            if (!tracker.add(x)) {
                return true;
            }
        }

        return false;
    }
}
