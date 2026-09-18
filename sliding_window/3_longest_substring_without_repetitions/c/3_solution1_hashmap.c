#include <string.h>

int lengthOfLongestSubstring(char *s) {
    int lastSeen[256];
    memset(lastSeen, -1, sizeof(lastSeen));

    int maxLen = 0, left = 0;
    int len = strlen(s);

    for (int right = 0; right < len; right++) {
        unsigned char c = s[right];

        if (lastSeen[c] >= left) {
            left = lastSeen[c] + 1;
        }

        lastSeen[c] = right;

        if (right - left + 1 > maxLen) {
            maxLen = right - left + 1;
        }
    }

    return maxLen;
}
