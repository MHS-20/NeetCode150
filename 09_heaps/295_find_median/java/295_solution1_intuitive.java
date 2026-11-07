import java.util.Collections;
import java.util.PriorityQueue;

class MedianFinder {
    private final PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder()); // left half
    private final PriorityQueue<Integer> minHeap = new PriorityQueue<>(); // right half

    public void addNum(int num) {
        if (!minHeap.isEmpty() && num >= minHeap.peek())
            minHeap.offer(num);
        else
            maxHeap.offer(num);

        if (maxHeap.size() > minHeap.size() + 1)
            minHeap.offer(maxHeap.poll());

        if (minHeap.size() > maxHeap.size())
            maxHeap.offer(minHeap.poll());
    }

    public double findMedian() {
        if ((minHeap.size() + maxHeap.size()) % 2 == 0)
            return (minHeap.peek() + maxHeap.peek()) / 2.0;
        return maxHeap.peek();
    }
}
