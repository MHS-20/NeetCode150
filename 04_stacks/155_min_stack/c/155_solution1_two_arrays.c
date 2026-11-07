#include <stdlib.h>

typedef struct {
    int *v;
    int *mins;
    int size;
    int cap;
} MinStack;

MinStack *minStackCreate() {
    MinStack *s = malloc(sizeof(MinStack));
    s->cap = 16;
    s->size = 0;
    s->v = malloc(s->cap * sizeof(int));
    s->mins = malloc(s->cap * sizeof(int));
    return s;
}

void minStackPush(MinStack *s, int value) {
    if (s->size == s->cap) {
        s->cap *= 2;
        s->v = realloc(s->v, s->cap * sizeof(int));
        s->mins = realloc(s->mins, s->cap * sizeof(int));
    }
    s->v[s->size] = value;

    int curMin = value;
    if (s->size > 0 && s->mins[s->size - 1] < value)
        curMin = s->mins[s->size - 1];
    s->mins[s->size] = curMin;
    s->size++;
}

void minStackPop(MinStack *s) { s->size--; }

int minStackTop(MinStack *s) { return s->v[s->size - 1]; }

int minStackGetMin(MinStack *s) { return s->mins[s->size - 1]; }

void minStackFree(MinStack *s) {
    free(s->v);
    free(s->mins);
    free(s);
}
