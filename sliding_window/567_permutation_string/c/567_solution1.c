#include <stdbool.h>
#include <string.h>

bool checkInclusion(char *s1, char *s2) {
    int n1 = strlen(s1);
    int n2 = strlen(s2);
    if (n1 > n2)
        return false;

    int s1freq[26] = {0}, windowfreq[26] = {0};
    for (int i = 0; i < n1; i++) {
        s1freq[s1[i] - 'a']++;
        windowfreq[s2[i] - 'a']++;
    }

    int match = 0;
    for (int i = 0; i < 26; i++)
        if (s1freq[i] == windowfreq[i])
            match++;
    if (match == 26)
        return true;

    int left = 0;
    for (int right = n1; right < n2; right++) {
        int r = s2[right] - 'a';
        int l = s2[left] - 'a';

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
