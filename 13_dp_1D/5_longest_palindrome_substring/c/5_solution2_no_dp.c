#include <stdlib.h>
#include <string.h>

// Grow outward from the center (left, right) while the ends match.
// Returns the length of the palindrome found.
static int expand(const char *s, int n, int left, int right) {
  while (left >= 0 && right < n && s[left] == s[right]) {
    left--;
    right++;
  }
  return right - left - 1;
}

char *longestPalindrome(char *s) {
  int n = strlen(s);
  int bestStart = 0, bestLen = 0;

  for (int i = 0; i < n; i++) {
    int oddLen = expand(s, n, i, i);      // center on a character: "aba"
    int evenLen = expand(s, n, i, i + 1); // center between two characters: "abba"
    int len = oddLen > evenLen ? oddLen : evenLen;

    if (len > bestLen) {
      bestLen = len;
      bestStart = i - (len - 1) / 2;
    }
  }

  char *res = malloc(bestLen + 1);
  memcpy(res, s + bestStart, bestLen);
  res[bestLen] = '\0';
  return res;
}
