import java.util.List;
import java.util.PriorityQueue;

/**
 * Definition of Interval:
 * public class Interval {
 *     public int start, end;
 *     public Interval(int start, int end) {
 *         this.start = start;
 *         this.end = end;
 *     }
 * }
 */

class Solution {
    public int minMeetingRooms(List<Interval> intervals) {
        int mx = 0;
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        intervals.sort((a, b) -> Integer.compare(a.start, b.start));

        for (Interval i : intervals) {
            while (!minHeap.isEmpty() && minHeap.peek() <= i.start)
                minHeap.poll();
            minHeap.offer(i.end);
            mx = Math.max(mx, minHeap.size());
        }

        return mx;
    }
}
