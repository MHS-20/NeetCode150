import java.util.PriorityQueue;

class KthLargest {
    private final int cap;
    private final PriorityQueue<Integer> pq = new PriorityQueue<>();

    public KthLargest(int k, int[] nums) {
        cap = k;
        for (int n : nums)
            add(n);
    }

    public int add(int val) {
        if (pq.size() < cap) {
            pq.offer(val);
        } else if (val > pq.peek()) {
            pq.poll();
            pq.offer(val);
        }
        return pq.peek();
    }
}
