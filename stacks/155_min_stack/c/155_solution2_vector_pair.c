#include <stdlib.h>

typedef struct {
    int value;
    int minSoFar; // minimum of everything up to and including value
} Entry;

typedef struct {
    Entry *st;
    int size;
    int cap;
} MinStack;

MinStack *minStackCreate() {
    MinStack *s = malloc(sizeof(MinStack));
    s->cap = 16;
    s->size = 0;
    s->st = malloc(s->cap * sizeof(Entry));
    return s;
}

void minStackPush(MinStack *s, int value) {
    if (s->size == s->cap) {
        s->cap *= 2;
        s->st = realloc(s->st, s->cap * sizeof(Entry));
    }
    int curMin = value;
    if (s->size > 0 && s->st[s->size - 1].minSoFar < value)
        curMin = s->st[s->size - 1].minSoFar;
    s->st[s->size++] = (Entry){value, curMin};
}

void minStackPop(MinStack *s) { s->size--; }

int minStackTop(MinStack *s) { return s->st[s->size - 1].value; }

int minStackGetMin(MinStack *s) { return s->st[s->size - 1].minSoFar; }

void minStackFree(MinStack *s) {
    free(s->st);
    free(s);
}
