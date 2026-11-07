import java.util.HashMap;
import java.util.Map;

class Solution {
    public int characterReplacement(String s, int k) {
        Map<Character, Integer> reps = new HashMap<>();
        int left = 0;
        int maxLen = k;
        int maxFreq = 0;

        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);
            reps.put(c, reps.getOrDefault(c, 0) + 1);
            maxFreq = Math.max(maxFreq, reps.get(c));

            if (right - left - maxFreq >= k) {
                char leftChar = s.charAt(left);
                reps.put(leftChar, reps.get(leftChar) - 1);
                left++;
            }

            maxLen = Math.max(maxLen, right - left + 1);
        }

        return maxLen;
    }
}
