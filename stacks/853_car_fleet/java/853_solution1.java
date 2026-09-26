import java.util.Arrays;

class Solution {
    public int carFleet(int target, int[] position, int[] speed) {
        int n = position.length;
        Integer[] idx = new Integer[n];
        for (int i = 0; i < n; i++)
            idx[i] = i;
        Arrays.sort(idx, (a, b) -> position[b] - position[a]);

        int fleets = 0;
        double slowest = 0; // arrival time of the fleet ahead
        for (int i : idx) {
            double hours = (double) (target - position[i]) / speed[i];
            if (hours > slowest) {
                fleets++;
                slowest = hours;
            }
        }
        return fleets;
    }
}
