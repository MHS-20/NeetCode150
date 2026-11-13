#include <stdlib.h>
#include <string.h>

static void expand(const char *s, int n, int l, int r, int *bestStart, int *bestLen) {
  // bounds first, so s[l] and s[r] are only read when valid
  while (l >= 0 && r < n && s[l] == s[r]) {
    l--;
    r++;
  }
  // pointers overshot by one on each side: palindrome is s[l+1 .. r-1]
  int len = r - l - 1;
  if (len > *bestLen) {
    *bestLen = len;
    *bestStart = l + 1;
  }
}

char *longestPalindrome(char *s) {
  int n = strlen(s), bestStart = 0, bestLen = 0;

  for (int i = 0; i < n; i++) {
    // odd-length palindromes, centered on s[i]
    expand(s, n, i, i, &bestStart, &bestLen);
    // even-length palindromes, centered between s[i] and s[i+1]
    expand(s, n, i, i + 1, &bestStart, &bestLen);
  }

  char *res = malloc(bestLen + 1);
  memcpy(res, s + bestStart, bestLen);
  res[bestLen] = '\0';
  return res;
}
