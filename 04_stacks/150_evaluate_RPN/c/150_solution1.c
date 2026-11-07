#include <stdlib.h>
#include <string.h>

int evalRPN(char **tokens, int tokensSize) {
    int *st = malloc(tokensSize * sizeof(int));
    int top = 0;

    for (int i = 0; i < tokensSize; i++) {
        char *s = tokens[i];
        // a lone operator char; "-11" is a number, so check the length too
        if (strlen(s) == 1 && strchr("+-*/", s[0])) {
            int b = st[--top];
            int a = st[--top];

            if (s[0] == '+')
                st[top++] = a + b;
            else if (s[0] == '-')
                st[top++] = a - b;
            else if (s[0] == '*')
                st[top++] = a * b;
            else
                st[top++] = a / b;
        } else {
            st[top++] = atoi(s);
        }
    }

    int result = st[top - 1];
    free(st);
    return result;
}
