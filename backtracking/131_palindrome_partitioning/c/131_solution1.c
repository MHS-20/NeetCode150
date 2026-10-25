#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char ***rows;
  int *colSizes;
  int size;
  int cap;
} Result;

static bool isPalindrome(const char *s, int l, int r) {
  while (l < r)
    if (s[l++] != s[r--])
      return false;
  return true;
}

static void save(Result *res, char **path, int pathSize) {
  if (res->size == res->cap) {
    res->cap = res->cap ? 2 * res->cap : 16;
    res->rows = realloc(res->rows, res->cap * sizeof(char **));
    res->colSizes = realloc(res->colSizes, res->cap * sizeof(int));
  }
  char **row = malloc(pathSize * sizeof(char *));
  for (int i = 0; i < pathSize; i++)
    row[i] = strdup(path[i]);
  res->rows[res->size] = row;
  res->colSizes[res->size++] = pathSize;
}

static void backtrack(const char *s, int n, int start, char **path,
                      int pathSize, Result *res) {
  if (start == n) {
    save(res, path, pathSize);
    return;
  }
  for (int i = start; i < n; i++) {
    if (!isPalindrome(s, start, i))
      continue;
    path[pathSize] = strndup(s + start, i - start + 1);
    backtrack(s, n, i + 1, path, pathSize + 1, res);
    free(path[pathSize]);
  }
}

char ***partition(char *s, int *returnSize, int **returnColumnSizes) {
  Result res = {0};
  int n = strlen(s);
  char **path = malloc((n ? n : 1) * sizeof(char *)); // at most n pieces
  backtrack(s, n, 0, path, 0, &res);
  free(path);
  *returnSize = res.size;
  *returnColumnSizes = res.colSizes;
  return res.rows;
}
