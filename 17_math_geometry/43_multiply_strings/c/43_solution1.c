#include <stdlib.h>
#include <string.h>

char *multiply(char *num1, char *num2) {
  int n = strlen(num1), m = strlen(num2);
  int *pos = calloc(n + m, sizeof(int));

  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      int mul = (num1[i] - '0') * (num2[j] - '0');
      int sum = mul + pos[i + j + 1];
      pos[i + j + 1] = sum % 10; // ones digit stays here
      pos[i + j] += sum / 10;    // carry goes one position left
    }
  }

  char *res = malloc(n + m + 1);
  int k = 0;
  for (int i = 0; i < n + m; i++)
    if (!(k == 0 && pos[i] == 0)) // skip leading zeros
      res[k++] = '0' + pos[i];
  if (k == 0)
    res[k++] = '0';
  res[k] = '\0';

  free(pos);
  return res;
}
