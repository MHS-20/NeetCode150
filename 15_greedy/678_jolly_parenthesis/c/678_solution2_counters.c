#include <stdbool.h>

// hi is the count if every * is a '('. If even that drops below 0, there's an
// unmatched ')' no matter what. lo is the count if every * is a ')'. Clamping
// it to 0 throws away choices that would close more than is open.
bool checkValidString(char *s) {
  int lo = 0, hi = 0; // min and max possible number of open '('

  for (; *s; s++) {
    if (*s == '(') {
      lo++;
      hi++;
    } else if (*s == ')') {
      lo--;
      hi--;
    } else {
      lo--;
      hi++;
    } // '*' could be ')' or '('

    if (hi < 0)
      return false; // too many ')', even with every '*' as '('
    if (lo < 0)
      lo = 0; // the count can't go negative, so drop those choices
  }

  return lo == 0; // some choice of '*' leaves zero open
}
