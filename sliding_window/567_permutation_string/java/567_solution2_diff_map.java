import java.util.HashMap;
import java.util.Map;

class Solution {
    private Map<Character, Integer> diff;
    private int mismatched;

    public boolean checkInclusion(String s1, String s2) {
        int k = s1.length();
        diff = new HashMap<>();
        mismatched = 0;

        for (char c : s1.toCharArray())
            update(c, -1);

        for (int right = 0; right < s2.length(); right++) {
            update(s2.charAt(right), +1); // char enters
            if (right >= k)
                update(s2.charAt(right - k), -1); // char leaves
            if (mismatched == 0)
                return true;
        }
        return false;
    }

    // shift a letter's diff by delta, keeping `mismatched` in sync
    private void update(char c, int delta) {
        int d = diff.getOrDefault(c, 0);
        if (d == 0)
            mismatched++; // was balanced, about to break
        diff.put(c, d + delta);
        if (d + delta == 0)
            mismatched--; // now balanced again
    }
}
