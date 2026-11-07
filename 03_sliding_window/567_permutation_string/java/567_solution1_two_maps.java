import java.util.HashMap;
import java.util.Map;

class Solution {
    private Map<Character, Integer> freq, wfreq;
    private int matches;

    public boolean checkInclusion(String s1, String s2) {
        int k = s1.length();
        freq = new HashMap<>();
        wfreq = new HashMap<>();
        for (char c : s1.toCharArray())
            freq.merge(c, 1, Integer::sum);

        int need = freq.size(); // distinct letters in s1, fixed from here on
        matches = 0;            // letters of s1 whose window count equals freq

        for (int right = 0; right < s2.length(); right++) {
            update(s2.charAt(right), +1); // char enters
            if (right >= k)
                update(s2.charAt(right - k), -1); // char leaves
            if (matches == need)
                return true;
        }
        return false;
    }

    // change the window count of c by delta, keeping `matches` in sync
    private void update(char c, int delta) {
        Integer target = freq.get(c);
        if (target == null)
            return; // not in s1: irrelevant
        int count = wfreq.getOrDefault(c, 0);
        if (count == target)
            matches--; // was matching, about to change
        wfreq.put(c, count + delta);
        if (count + delta == target)
            matches++; // matches now
    }
}
