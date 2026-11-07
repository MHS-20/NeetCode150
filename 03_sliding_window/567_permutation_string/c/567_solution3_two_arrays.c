#include <stdbool.h>
#include <string.h>

static int freq[26], wfreq[26];
static int matches;

// change the window count of a letter by delta, keeping `matches` in sync
static void update(char ch, int delta) {
    int c = ch - 'a';
    if (wfreq[c] == freq[c])
        matches--; // was matching, about to change
    wfreq[c] += delta;
    if (wfreq[c] == freq[c])
        matches++; // matches now
}

bool checkInclusion(char *s1, char *s2) {
    int k = strlen(s1), n = strlen(s2);
    memset(freq, 0, sizeof freq);
    memset(wfreq, 0, sizeof wfreq);
    for (int i = 0; i < k; i++)
        freq[s1[i] - 'a']++;

    // matches = number of the 26 letters whose window count equals freq
    matches = 0;
    for (int i = 0; i < 26; i++)
        if (freq[i] == wfreq[i])
            matches++; // empty window: letters absent from s1 already match

    for (int right = 0; right < n; right++) {
        update(s2[right], +1); // char enters
        if (right >= k)
            update(s2[right - k], -1); // char leaves
        if (matches == 26)
            return true;
    }
    return false;
}
