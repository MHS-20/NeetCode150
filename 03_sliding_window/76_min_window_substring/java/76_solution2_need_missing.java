class Solution {
    public String minWindow(String s, String t) {
        int[] need = new int[128];
        for (char c : t.toCharArray())
            need[c]++;
        int missing = t.length();

        int bestStart = 0, bestLen = Integer.MAX_VALUE;
        int left = 0;

        for (int right = 0; right < s.length(); right++) {
            if (need[s.charAt(right)]-- > 0)
                missing--; // this char was still needed

            while (missing == 0) { // window is valid: try to shrink
                if (right - left + 1 < bestLen) {
                    bestStart = left;
                    bestLen = right - left + 1;
                }
                if (++need[s.charAt(left)] > 0)
                    missing++; // we just removed a needed char
                left++;
            }
        }
        return bestLen == Integer.MAX_VALUE ? "" : s.substring(bestStart, bestStart + bestLen);
    }
}
