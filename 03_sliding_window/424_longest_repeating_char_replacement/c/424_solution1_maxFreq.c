#include <string.h>

int characterReplacement(char *s, int k) {
    int reps[26] = {0};
    int left = 0;
    int maxLen = k;
    int maxFreq = 0;
    int len = strlen(s);

    for (int right = 0; right < len; right++) {
        int c = s[right] - 'A';
        reps[c]++;

        if (reps[c] > maxFreq) {
            maxFreq = reps[c];
        }

        if (right - left - maxFreq >= k) {
            reps[s[left] - 'A']--;
            left++;
        }

        if (right - left + 1 > maxLen) {
            maxLen = right - left + 1;
        }
    }

    return maxLen;
}
