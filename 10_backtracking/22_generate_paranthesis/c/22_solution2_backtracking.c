#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} Result;

static void backtrack(int n, int opened, int closed, char *cur, Result *res) {
    int len = opened + closed;
    if (closed == n) { // implies opened == n too
        cur[len] = '\0';
        res->items[res->size++] = strdup(cur); // copies once, only for finished answers
        return;
    }

    if (opened < n) {
        cur[len] = '(';                          // choose
        backtrack(n, opened + 1, closed, cur, res); // explore
        // undo is implicit: len is derived from the counters, so the next
        // write simply overwrites this slot
    }

    if (closed < opened) {
        cur[len] = ')';
        backtrack(n, opened, closed + 1, cur, res);
    }
}

// Catalan(n) = C(2n, n) / (n + 1), computed iteratively
static long catalan(int n) {
    long c = 1;
    for (int i = 0; i < n; i++)
        c = c * 2 * (2 * i + 1) / (i + 2);
    return c;
}

char **generateParenthesis(int n, int *returnSize) {
    Result res = {malloc(catalan(n) * sizeof(char *)), 0};
    char *cur = malloc(2 * n + 1);
    backtrack(n, 0, 0, cur, &res);
    free(cur);
    *returnSize = res.size;
    return res.items;
}
