import java.util.Map;
import java.util.TreeMap;

class Solution {
    public boolean isNStraightHand(int[] hand, int groupSize) {
        if (hand.length % groupSize != 0)
            return false;

        TreeMap<Integer, Integer> count = new TreeMap<>();
        for (int c : hand)
            count.merge(c, 1, Integer::sum);

        while (!count.isEmpty()) {
            int start = count.firstKey(); // smallest remaining card

            for (int v = start; v < start + groupSize; v++) {
                Integer left = count.get(v);
                if (left == null)
                    return false; // missing value, group can't be built
                if (left == 1)
                    count.remove(v); // drop values that are used up
                else
                    count.put(v, left - 1);
            }
        }

        return true;
    }
}
