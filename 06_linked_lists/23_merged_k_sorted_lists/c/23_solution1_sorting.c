#include "list_node.h"
#include <stdlib.h>

static int cmp_int(const void *a, const void *b) {
  int x = *(const int *)a, y = *(const int *)b;
  return (x > y) - (x < y);
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize) {
  // 1. collect every value from every list
  int count = 0;
  for (int i = 0; i < listsSize; i++)
    for (struct ListNode *p = lists[i]; p; p = p->next)
      count++;

  if (count == 0)
    return NULL;

  int *vals = malloc(count * sizeof(int));
  int k = 0;
  for (int i = 0; i < listsSize; i++)
    for (struct ListNode *p = lists[i]; p; p = p->next)
      vals[k++] = p->val;

  // 2. sort them
  qsort(vals, count, sizeof(int), cmp_int);

  // 3. rebuild a new list
  struct ListNode dummy;
  struct ListNode *cur = &dummy;
  for (int i = 0; i < count; i++) {
    cur->next = malloc(sizeof(struct ListNode));
    cur = cur->next;
    cur->val = vals[i];
    cur->next = NULL;
  }

  free(vals);
  return dummy.next;
}
