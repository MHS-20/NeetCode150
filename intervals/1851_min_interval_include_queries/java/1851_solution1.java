import java.util.Arrays;
import java.util.PriorityQueue;

class Solution {
    public int[] minInterval(int[][] intervals, int[] queries) {
        int[] result = new int[queries.length];
        Integer[] idx = new Integer[queries.length];
        for (int k = 0; k < idx.length; k++)
            idx[k] = k;
        // {size, end}, ordered by size then end
        PriorityQueue<int[]> minHeap = new PriorityQueue<>(
                (a, b) -> a[0] != b[0] ? Integer.compare(a[0], b[0]) : Integer.compare(a[1], b[1]));

        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));
        Arrays.sort(idx, (a, b) -> Integer.compare(queries[a], queries[b]));

        int i = 0, n = intervals.length;
        for (int j : idx) {
            int q = queries[j];

            while (i < n && intervals[i][0] <= q) {
                minHeap.add(new int[] { intervals[i][1] - intervals[i][0] + 1, intervals[i][1] });
                i++;
            }

            while (!minHeap.isEmpty() && minHeap.peek()[1] < q)
                minHeap.poll();

            result[j] = minHeap.isEmpty() ? -1 : minHeap.peek()[0];
        }

        return result;
    }
}
