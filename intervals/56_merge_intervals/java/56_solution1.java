import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public int[][] merge(int[][] intervals) {
        Arrays.sort(intervals, (a, b) -> a[0] != b[0] ? Integer.compare(a[0], b[0]) : Integer.compare(a[1], b[1]));
        List<int[]> result = new ArrayList<>();

        for (int[] cur : intervals) {
            if (result.isEmpty() || result.get(result.size() - 1)[1] < cur[0])
                result.add(cur);
            else {
                int[] last = result.get(result.size() - 1);
                last[1] = Math.max(last[1], cur[1]);
            }
        }

        return result.toArray(new int[0][]);
    }
}
