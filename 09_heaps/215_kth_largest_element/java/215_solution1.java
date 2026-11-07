import java.util.PriorityQueue;

class Solution {
    public int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int x : nums) {
            if (pq.size() < k) {
                pq.offer(x);
            } else if (x > pq.peek()) {
                pq.poll();
                pq.offer(x);
            }
        }
        return pq.peek();
    }
}
