#include <stdbool.h>
#include <string.h>

// C has no hash map: a 128-slot array indexed by char stands in for one
static int freq[128], wfreq[128];
static int matches;

// change the window count of c by delta, keeping `matches` in sync
static void update(char c, int delta) {
    if (freq[(int)c] == 0)
        return; // not in s1: irrelevant
    if (wfreq[(int)c] == freq[(int)c])
        matches--; // was matching, about to change
    wfreq[(int)c] += delta;
    if (wfreq[(int)c] == freq[(int)c])
        matches++; // matches now
}

bool checkInclusion(char *s1, char *s2) {
    int k = strlen(s1), n = strlen(s2);
    memset(freq, 0, sizeof freq);
    memset(wfreq, 0, sizeof wfreq);

    int need = 0; // distinct letters in s1, fixed from here on
    for (int i = 0; i < k; i++)
        if (freq[(int)s1[i]]++ == 0)
            need++;
    matches = 0; // letters of s1 whose window count equals freq

    for (int right = 0; right < n; right++) {
        update(s2[right], +1); // char enters
        if (right >= k)
            update(s2[right - k], -1); // char leaves
        if (matches == need)
            return true;
    }
    return false;
}
