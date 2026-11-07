import java.util.Arrays;

class Solution {
    public int eraseOverlapIntervals(int[][] intervals) {
        Arrays.sort(intervals, (a, b) -> a[0] != b[0] ? Integer.compare(a[0], b[0]) : Integer.compare(a[1], b[1]));
        int kept = 0;
        int lastEnd = 0; // end of the last kept interval

        for (int[] cur : intervals) {
            if (kept == 0 || lastEnd <= cur[0]) {
                kept++;
                lastEnd = cur[1];
            } else if (lastEnd > cur[1]) {
                lastEnd = cur[1]; // overlap: keep the one that ends earlier
            }
        }

        return intervals.length - kept;
    }
}
