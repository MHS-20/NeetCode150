#include <stdlib.h>
#include <string.h>

char *encode(char **strs, int strsSize) {
    size_t total = 1;
    for (int i = 0; i < strsSize; i++) {
        total += strlen(strs[i]) + 12;
    }

    char *encoded = malloc(total);
    encoded[0] = '\0';

    for (int i = 0; i < strsSize; i++) {
        char buf[16];
        sprintf(buf, "%zu-", strlen(strs[i]));
        strcat(encoded, buf);
        strcat(encoded, strs[i]);
    }

    return encoded;
}

char **decode(char *s, int *retSize) {
    int capacity = 16;
    char **res = malloc(capacity * sizeof(char *));
    int count = 0;

    size_t i = 0;
    size_t n = strlen(s);

    while (i < n) {
        char *delim = strchr(s + i, '-');
        size_t delimPos = delim - s;
        int len = atoi(s + i);

        if (count == capacity) {
            capacity *= 2;
            res = realloc(res, capacity * sizeof(char *));
        }

        char *str = malloc(len + 1);
        memcpy(str, s + delimPos + 1, len);
        str[len] = '\0';
        res[count++] = str;

        i = delimPos + 1 + len;
    }

    *retSize = count;
    return res;
}
