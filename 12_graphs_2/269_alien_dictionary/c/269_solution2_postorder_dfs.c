#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Returns false if a cycle is found
static bool dfs(int u, bool edge[26][26], int *state, char *result, int *n) {
  state[u] = 1;
  for (int v = 0; v < 26; v++) {
    if (!edge[u][v])
      continue;
    if (state[v] == 1)
      return false; // back edge: cycle
    if (state[v] == 0 && !dfs(v, edge, state, result, n))
      return false; // propagate failure
  }
  state[u] = 2;
  result[(*n)++] = 'a' + u; // post-order
  return true;
}

char *foreignDictionary(char **words, int wordsSize) {
  bool seen[26] = {0};
  bool edge[26][26] = {{0}};
  int state[26] = {0}; // 0 = unvisited, 1 = visiting, 2 = done

  // 1. Register every letter
  for (int i = 0; i < wordsSize; i++)
    for (char *p = words[i]; *p; p++)
      seen[*p - 'a'] = true;

  // 2. Build edges (no in-degree needed)
  for (int i = 0; i + 1 < wordsSize; i++) {
    const char *a = words[i], *b = words[i + 1];
    int la = strlen(a), lb = strlen(b);
    int len = la < lb ? la : lb;
    int j = 0;
    while (j < len && a[j] == b[j])
      j++;

    if (j == len) {
      if (la > lb)
        return strdup("");
      continue;
    }
    edge[a[j] - 'a'][b[j] - 'a'] = true; // duplicates are harmless here
  }

  // 3. DFS from every unvisited letter
  char *result = malloc(27);
  int n = 0;
  for (int c = 0; c < 26; c++)
    if (seen[c] && state[c] == 0 && !dfs(c, edge, state, result, &n)) {
      result[0] = '\0';
      return result;
    }

  // 4. Post-order is reversed topological order
  for (int i = 0; i < n / 2; i++) {
    char t = result[i];
    result[i] = result[n - 1 - i];
    result[n - 1 - i] = t;
  }
  result[n] = '\0';
  return result;
}
