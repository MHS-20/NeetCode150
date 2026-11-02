#include <stdlib.h>
#include <string.h>

#define CODES (26 * 26 * 26) // airport codes are 3 uppercase letters

static int code(const char *s) {
  return ((s[0] - 'A') * 26 + (s[1] - 'A')) * 26 + (s[2] - 'A');
}

static int cmpDesc(const void *a, const void *b) {
  return strcmp(*(char *const *)b, *(char *const *)a);
}

// C has no heap of strings: sort each destination list descending
// and pop from the back, which yields the smallest first
static char ***adj;
static int *adjLen;
static char **result;
static int resultLen;

static void dfs(char *cur) {
  int c = code(cur);
  while (adjLen[c] > 0) {
    char *next = adj[c][--adjLen[c]]; // use this ticket
    dfs(next);
  }
  result[resultLen++] = cur; // post-order: no tickets left here
}

char **findItinerary(char ***tickets, int ticketsSize, int *ticketsColSize,
                     int *returnSize) {
  (void)ticketsColSize; // always 2
  adj = calloc(CODES, sizeof(char **));
  adjLen = calloc(CODES, sizeof(int));
  int *adjCap = calloc(CODES, sizeof(int));

  for (int i = 0; i < ticketsSize; i++) {
    int c = code(tickets[i][0]);
    if (adjLen[c] == adjCap[c]) {
      adjCap[c] = adjCap[c] ? 2 * adjCap[c] : 2;
      adj[c] = realloc(adj[c], adjCap[c] * sizeof(char *));
    }
    adj[c][adjLen[c]++] = tickets[i][1];
  }
  for (int c = 0; c < CODES; c++)
    if (adjLen[c] > 1)
      qsort(adj[c], adjLen[c], sizeof(char *), cmpDesc);

  result = malloc((ticketsSize + 1) * sizeof(char *));
  resultLen = 0;
  dfs("JFK");

  for (int i = 0; i < resultLen / 2; i++) {
    char *t = result[i];
    result[i] = result[resultLen - 1 - i];
    result[resultLen - 1 - i] = t;
  }

  for (int c = 0; c < CODES; c++)
    free(adj[c]);
  free(adj);
  free(adjLen);
  free(adjCap);
  *returnSize = resultLen;
  return result; // points into tickets, plus the literal "JFK"
}
