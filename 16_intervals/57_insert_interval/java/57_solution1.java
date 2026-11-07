import java.util.ArrayList;
import java.util.List;

class Solution {
    public int[][] insert(int[][] intervals, int[] newInterval) {
        List<int[]> result = new ArrayList<>();
        int i = 0, n = intervals.length;

        // 1. Intervals entirely before newInterval
        while (i < n && intervals[i][1] < newInterval[0])
            result.add(intervals[i++]);

        // 2. Intervals overlapping newInterval: absorb them into it
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = Math.min(newInterval[0], intervals[i][0]);
            newInterval[1] = Math.max(newInterval[1], intervals[i][1]);
            i++;
        }
        result.add(newInterval);

        // 3. Intervals entirely after newInterval
        while (i < n)
            result.add(intervals[i++]);

        return result.toArray(new int[0][]);
    }
}
