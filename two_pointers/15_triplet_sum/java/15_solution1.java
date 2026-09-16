import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> result = new ArrayList<>();

        for (int idx = 0; idx < nums.length; idx++) {
            if (idx > 0 && nums[idx] == nums[idx - 1]) {
                continue;
            }

            int left = idx + 1, right = nums.length - 1;

            while (left < right) {
                int total = nums[idx] + nums[left] + nums[right];

                if (total == 0) {
                    result.add(Arrays.asList(nums[idx], nums[left], nums[right]));
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right + 1]) {
                        right--;
                    }
                } else if (total > 0) {
                    right--;
                } else {
                    left++;
                }
            }
        }

        return result;
    }
}
