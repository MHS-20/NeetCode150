#include <stdbool.h>
#include <stdlib.h>

/**
 * Definition of Interval:
 * typedef struct {
 *     int start, end;
 * } Interval;
 */

static int cmpStart(const void *a, const void *b) {
  const Interval *x = a, *y = b;
  return (x->start > y->start) - (x->start < y->start);
}

bool canAttendMeetings(Interval *intervals, int intervalsSize) {
  qsort(intervals, intervalsSize, sizeof(Interval), cmpStart);
  for (int i = 0; i < intervalsSize - 1; i++) {
    if (intervals[i].end > intervals[i + 1].start)
      return false;
  }
  return true;
}
