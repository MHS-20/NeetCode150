class Solution {
    private int bestStart = 0, bestLen = 0;

    public String longestPalindrome(String s) {
        for (int i = 0; i < s.length(); i++) {
            // odd-length palindromes, centered on s[i]
            expand(s, i, i);
            // even-length palindromes, centered between s[i] and s[i+1]
            expand(s, i, i + 1);
        }

        return s.substring(bestStart, bestStart + bestLen);
    }

    private void expand(String s, int l, int r) {
        // bounds first, so s[l] and s[r] are only read when valid
        while (l >= 0 && r < s.length() && s.charAt(l) == s.charAt(r)) {
            l--;
            r++;
        }
        // pointers overshot by one on each side: palindrome is s[l+1 .. r-1]
        int len = r - l - 1;
        if (len > bestLen) {
            bestLen = len;
            bestStart = l + 1;
        }
    }
}
