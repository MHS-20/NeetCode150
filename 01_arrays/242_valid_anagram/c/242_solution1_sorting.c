#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int cmp(const void *a, const void *b) {
    return (*(const unsigned char *)a) - (*(const unsigned char *)b);
}

bool isAnagram(char *s, char *t) {
    size_t sLen = strlen(s);
    size_t tLen = strlen(t);
    if (sLen != tLen) {
        return false;
    }

    char *sCopy = strdup(s);
    char *tCopy = strdup(t);
    qsort(sCopy, sLen, sizeof(char), cmp);
    qsort(tCopy, tLen, sizeof(char), cmp);

    bool result = strcmp(sCopy, tCopy) == 0;

    free(sCopy);
    free(tCopy);
    return result;
}
