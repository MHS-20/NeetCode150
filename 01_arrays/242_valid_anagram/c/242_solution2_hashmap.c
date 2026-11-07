#include <stdbool.h>
#include <string.h>

bool isAnagram(char *s, char *t) {
    size_t sLen = strlen(s);
    size_t tLen = strlen(t);
    if (sLen != tLen) {
        return false;
    }

    /* byte-value histogram: stands in for a hashmap over the 0-255 key space */
    int counts[256] = {0};
    for (size_t i = 0; i < sLen; i++) {
        counts[(unsigned char)s[i]]++;
    }

    for (size_t i = 0; i < tLen; i++) {
        counts[(unsigned char)t[i]]--;
        if (counts[(unsigned char)t[i]] < 0) {
            return false;
        }
    }

    return true;
}
