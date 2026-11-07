/* works if chars are a-z only */
#include <stdbool.h>
#include <string.h>

bool isAnagram(char *s, char *t) {
    size_t sLen = strlen(s);
    size_t tLen = strlen(t);
    if (sLen != tLen) {
        return false;
    }

    int count[26] = {0};
    for (size_t i = 0; i < sLen; i++) {
        count[s[i] - 'a']++;
        count[t[i] - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            return false;
        }
    }

    return true;
}
