#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int cmpStr(const void *a, const void *b) {
  return strcmp(*(char *const *)a, *(char *const *)b);
}

// index of w in the sorted dictionary, or -1
static int lookup(char **sorted, int n, const char *w) {
  char **hit = bsearch(&w, sorted, n, sizeof(char *), cmpStr);
  return hit ? (int)(hit - sorted) : -1;
}

int ladderLength(char *beginWord, char *endWord, char **wordList,
                 int wordListSize) {
  // C has no hash set: sort the words and binary-search them instead,
  // with a parallel flag array standing in for erase()
  int n = wordListSize, len = strlen(beginWord);
  char **words = malloc(n * sizeof(char *));
  memcpy(words, wordList, n * sizeof(char *));
  qsort(words, n, sizeof(char *), cmpStr);
  bool *removed = calloc(n, sizeof(bool));

  int result = 0;
  if (lookup(words, n, endWord) < 0)
    goto done;

  // each word is enqueued at most once, plus beginWord
  char **q = malloc((n + 1) * sizeof(char *));
  int head = 0, tail = 0;
  q[tail++] = beginWord;
  int b = lookup(words, n, beginWord);
  if (b >= 0)
    removed[b] = true;
  int length = 1;
  char *w = malloc(len + 1);

  while (head < tail) {
    int levelEnd = tail;
    while (head < levelEnd) {
      strcpy(w, q[head++]);

      for (int pos = 0; pos < len; pos++) {
        char original = w[pos];
        for (char c = 'a'; c <= 'z'; c++) {
          if (c == original)
            continue;
          w[pos] = c;
          if (strcmp(w, endWord) == 0) {
            result = length + 1;
            goto cleanup;
          }
          int k = lookup(words, n, w);
          if (k >= 0 && !removed[k]) {
            removed[k] = true;
            q[tail++] = words[k];
          }
        }
        w[pos] = original;
      }
    }
    length++;
  }

cleanup:
  free(w);
  free(q);
done:
  free(removed);
  free(words);
  return result;
}
