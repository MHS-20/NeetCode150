class Solution {
    // Grow outward from the center (left, right) while the ends match.
    // Returns the length of the palindrome found.
    private int expand(String s, int left, int right) {
        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }
        return right - left - 1;
    }

    public String longestPalindrome(String s) {
        int bestStart = 0, bestLen = 0;

        for (int i = 0; i < s.length(); i++) {
            int oddLen = expand(s, i, i); // center on a character: "aba"
            int evenLen = expand(s, i, i + 1); // center between two characters: "abba"
            int len = Math.max(oddLen, evenLen);

            if (len > bestLen) {
                bestLen = len;
                bestStart = i - (len - 1) / 2;
            }
        }
        return s.substring(bestStart, bestStart + bestLen);
    }
}
