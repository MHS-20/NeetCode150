class Solution {
    public boolean checkInclusion(String s1, String s2) {
        if (s1.length() > s2.length())
            return false;

        int[] s1freq = new int[26];
        int[] windowfreq = new int[26];
        for (int i = 0; i < s1.length(); i++) {
            s1freq[s1.charAt(i) - 'a']++;
            windowfreq[s2.charAt(i) - 'a']++;
        }

        int match = 0;
        for (int i = 0; i < 26; i++)
            if (s1freq[i] == windowfreq[i])
                match++;
        if (match == 26)
            return true;

        int left = 0;
        for (int right = s1.length(); right < s2.length(); right++) {
            int r = s2.charAt(right) - 'a';
            int l = s2.charAt(left) - 'a';

            // add right char
            if (windowfreq[r] == s1freq[r])
                match--;
            windowfreq[r]++;
            if (windowfreq[r] == s1freq[r])
                match++;

            // remove left char
            if (windowfreq[l] == s1freq[l])
                match--;
            windowfreq[l]--;
            if (windowfreq[l] == s1freq[l])
                match++;

            left++;
            if (match == 26)
                return true;
        }
        return false;
    }
}
