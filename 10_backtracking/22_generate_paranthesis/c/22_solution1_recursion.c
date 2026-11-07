#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} Result;

// each call gets its own copy of the prefix, like passing a string by value
static void build(int n, int opened, int closed, const char *cur, Result *res) {
    int len = opened + closed;
    if (closed == n) { // implies opened == n too
        res->items[res->size++] = strdup(cur);
        return;
    }

    char next[2 * n + 1];
    memcpy(next, cur, len);
    next[len + 1] = '\0';

    if (opened < n) {
        next[len] = '(';
        build(n, opened + 1, closed, next, res);
    }
    if (closed < opened) {
        next[len] = ')';
        build(n, opened, closed + 1, next, res);
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
    build(n, 0, 0, "", &res);
    *returnSize = res.size;
    return res.items;
}
