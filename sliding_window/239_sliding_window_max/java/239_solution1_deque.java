import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        int[] maxs = new int[nums.length - k + 1];
        Deque<Integer> dq = new ArrayDeque<>(); // indices, values decreasing

        // i is the right pointer
        // i - k + 1 is the left pointer
        for (int i = 0; i < nums.length; i++) {
            if (!dq.isEmpty() && dq.peekFirst() < i - k + 1)
                dq.pollFirst();

            while (!dq.isEmpty() && nums[i] > nums[dq.peekLast()])
                dq.pollLast();
            dq.offerLast(i);

            if (i >= k - 1)
                maxs[i - k + 1] = nums[dq.peekFirst()];
        }

        return maxs;
    }
}
