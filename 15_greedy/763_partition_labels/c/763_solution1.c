#include <stdlib.h>
#include <string.h>

int *partitionLabels(char *s, int *returnSize) {
  int n = strlen(s);
  int last[26];
  for (int i = 0; i < n; i++)
    last[s[i] - 'a'] = i;

  // at most one partition per character
  int *result = malloc((n > 0 ? n : 1) * sizeof(int));
  int count = 0, start = 0, end = 0;

  for (int i = 0; i < n; i++) {
    if (last[s[i] - 'a'] > end)
      end = last[s[i] - 'a'];
    if (i == end) {
      result[count++] = end - start + 1;
      start = i + 1;
    }
  }

  *returnSize = count;
  return result;
}
