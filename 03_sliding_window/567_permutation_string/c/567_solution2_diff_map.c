#include <stdbool.h>
#include <string.h>

// C has no hash map: a 128-slot array indexed by char stands in for one
static int diff[128];
static int mismatched;

// shift a letter's diff by delta, keeping `mismatched` in sync
static void update(char c, int delta) {
    if (diff[(int)c] == 0)
        mismatched++; // was balanced, about to break
    diff[(int)c] += delta;
    if (diff[(int)c] == 0)
        mismatched--; // now balanced again
}

bool checkInclusion(char *s1, char *s2) {
    int k = strlen(s1), n = strlen(s2);
    memset(diff, 0, sizeof diff);
    mismatched = 0;

    for (int i = 0; i < k; i++)
        update(s1[i], -1);

    for (int right = 0; right < n; right++) {
        update(s2[right], +1); // char enters
        if (right >= k)
            update(s2[right - k], -1); // char leaves
        if (mismatched == 0)
            return true;
    }
    return false;
}
