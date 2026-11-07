class Solution {
    private int[] freq, wfreq;
    private int matches;

    public boolean checkInclusion(String s1, String s2) {
        int k = s1.length();
        freq = new int[26];
        wfreq = new int[26];
        for (char ch : s1.toCharArray())
            freq[ch - 'a']++;

        // matches = number of the 26 letters whose window count equals freq
        matches = 0;
        for (int i = 0; i < 26; i++)
            if (freq[i] == wfreq[i])
                matches++; // empty window: letters absent from s1 already match

        for (int right = 0; right < s2.length(); right++) {
            update(s2.charAt(right), +1); // char enters
            if (right >= k)
                update(s2.charAt(right - k), -1); // char leaves
            if (matches == 26)
                return true;
        }
        return false;
    }

    // change the window count of a letter by delta, keeping `matches` in sync
    private void update(char ch, int delta) {
        int c = ch - 'a';
        if (wfreq[c] == freq[c])
            matches--; // was matching, about to change
        wfreq[c] += delta;
        if (wfreq[c] == freq[c])
            matches++; // matches now
    }
}
