#include <limits.h>
#include <stdlib.h>
#include <string.h>

char *minWindow(char *s, char *t) {
    int need[128] = {0};
    int ns = strlen(s), nt = strlen(t);
    for (int i = 0; i < nt; i++)
        need[(int)t[i]]++;
    int missing = nt;

    int bestStart = 0, bestLen = INT_MAX;
    int left = 0;

    for (int right = 0; right < ns; right++) {
        if (need[(int)s[right]]-- > 0)
            missing--; // this char was still needed

        while (missing == 0) { // window is valid: try to shrink
            if (right - left + 1 < bestLen) {
                bestStart = left;
                bestLen = right - left + 1;
            }
            if (++need[(int)s[left]] > 0)
                missing++; // we just removed a needed char
            left++;
        }
    }

    int len = bestLen == INT_MAX ? 0 : bestLen;
    char *res = malloc(len + 1);
    memcpy(res, s + bestStart, len);
    res[len] = '\0';
    return res;
}
