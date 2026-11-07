#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool checkValidString(char *s) {
  int n = strlen(s);
  // indices of unmatched '(' and '*'
  int *open = malloc((n ? n : 1) * sizeof(int));
  int *star = malloc((n ? n : 1) * sizeof(int));
  int openTop = 0, starTop = 0;
  bool ok = true;

  for (int i = 0; i < n && ok; i++) {
    switch (s[i]) {
    case '(':
      open[openTop++] = i;
      break;
    case '*':
      star[starTop++] = i;
      break;
    case ')':
      if (openTop > 0)
        openTop--;
      else if (starTop > 0)
        starTop--;
      else
        ok = false;
      break;
    }
  }

  // each leftover '(' needs a later '*' to close it
  while (ok && openTop > 0) {
    if (starTop == 0 || star[starTop - 1] < open[openTop - 1])
      ok = false;
    else {
      openTop--;
      starTop--;
    }
  }

  free(open);
  free(star);
  return ok;
}
