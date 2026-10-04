class Solution {
    public int findDuplicate(int[] nums) {
        int left = 1, right = nums.length - 1; // right = n

        while (left < right) {
            int mid = left + (right - left) / 2;

            // count how many numbers are <= mid
            int count = 0;
            for (int x : nums)
                if (x <= mid)
                    count++;

            if (count > mid)
                right = mid; // duplicate is in [left, mid]
            else
                left = mid + 1; // duplicate is in [mid + 1, right]
        }

        return left;
    }
}
