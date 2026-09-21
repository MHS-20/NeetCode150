#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isValid(char *s) {
    int n = strlen(s);
    char *expected = malloc(n + 1); // closing brackets we still owe
    int top = 0;

    for (int i = 0; i < n; i++) {
        switch (s[i]) {
        case '(':
            expected[top++] = ')';
            break;
        case '[':
            expected[top++] = ']';
            break;
        case '{':
            expected[top++] = '}';
            break;
        default:
            if (top == 0 || expected[--top] != s[i]) {
                free(expected);
                return false;
            }
        }
    }
    bool valid = top == 0;
    free(expected);
    return valid;
}
