import java.util.Collections;
import java.util.PriorityQueue;

class MedianFinder {
    private final PriorityQueue<Integer> lo = new PriorityQueue<>(Collections.reverseOrder()); // lower half
    private final PriorityQueue<Integer> hi = new PriorityQueue<>(); // upper half

    public void addNum(int num) {
        lo.offer(num);
        hi.offer(lo.poll());
        if (hi.size() > lo.size())
            lo.offer(hi.poll());
    }

    public double findMedian() {
        if (lo.size() > hi.size())
            return lo.peek();
        return (lo.peek() + hi.peek()) / 2.0;
    }
}
