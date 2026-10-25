#include <stdlib.h>
#include <string.h>

static const char *mapping[10] = {"",    "",    "abc",  "def", "ghi",
                                  "jkl", "mno", "pqrs", "tuv", "wxyz"};

static void backtrack(const char *digits, int n, int idx, char *cur,
                      char **result, int *returnSize) {
  if (idx == n) {
    result[(*returnSize)++] = strdup(cur);
    return;
  }
  for (const char *ch = mapping[digits[idx] - '0']; *ch; ch++) {
    cur[idx] = *ch; // choose
    backtrack(digits, n, idx + 1, cur, result, returnSize);
  } // un-choose is implicit: cur[idx] is overwritten next time
}

char **letterCombinations(char *digits, int *returnSize) {
  *returnSize = 0;
  int n = strlen(digits);
  if (n == 0)
    return NULL;

  int total = 1;
  for (int i = 0; i < n; i++)
    total *= strlen(mapping[digits[i] - '0']);

  char **result = malloc(total * sizeof(char *));
  char *cur = calloc(n + 1, 1);
  backtrack(digits, n, 0, cur, result, returnSize);
  free(cur);
  return result;
}
