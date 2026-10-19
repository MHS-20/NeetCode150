import java.util.PriorityQueue;

class KthLargest {
    private final int cap;
    private final PriorityQueue<Integer> pq = new PriorityQueue<>();

    public KthLargest(int k, int[] nums) {
        cap = k;
        for (int n : nums)
            pq.offer(n);
        while (pq.size() > cap)
            pq.poll();
    }

    public int add(int val) {
        pq.offer(val);
        if (pq.size() > cap)
            pq.poll();
        return pq.peek();
    }
}
