#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *foreignDictionary(char **words, int wordsSize) {
  bool seen[26] = {0};
  bool edge[26][26] = {{0}};
  int indeg[26] = {0};
  int total = 0;

  for (int i = 0; i < wordsSize; i++)
    for (char *p = words[i]; *p; p++)
      if (!seen[*p - 'a']) {
        seen[*p - 'a'] = true;
        total++;
      }

  for (int i = 0; i + 1 < wordsSize; i++) {
    const char *a = words[i], *b = words[i + 1];
    int la = strlen(a), lb = strlen(b);
    int len = la < lb ? la : lb;
    int j = 0;
    while (j < len && a[j] == b[j])
      j++;

    if (j == len) {
      if (la > lb)
        return strdup(""); // b is a proper prefix of a: invalid
      continue;
    }
    int u = a[j] - 'a', v = b[j] - 'a';
    if (!edge[u][v]) { // avoid double-counting
      edge[u][v] = true;
      indeg[v]++;
    }
  }

  // Kahn's algorithm; the queue never holds more than 26 letters in total
  int q[26], head = 0, tail = 0;
  for (int c = 0; c < 26; c++)
    if (seen[c] && indeg[c] == 0)
      q[tail++] = c;

  char *result = malloc(total + 1);
  int n = 0;
  while (head < tail) {
    int u = q[head++];
    result[n++] = 'a' + u;
    for (int v = 0; v < 26; v++)
      if (edge[u][v] && --indeg[v] == 0)
        q[tail++] = v;
  }
  result[n] = '\0';

  if (n != total) {
    result[0] = '\0';
  }
  return result;
}
