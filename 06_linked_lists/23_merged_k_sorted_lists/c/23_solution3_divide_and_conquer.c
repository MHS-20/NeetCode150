#include "list_node.h"

static struct ListNode *mergeTwo(struct ListNode *a, struct ListNode *b) {
  struct ListNode dummy;
  struct ListNode *cur = &dummy;
  while (a && b) {
    if (a->val <= b->val) {
      cur->next = a;
      a = a->next;
    } else {
      cur->next = b;
      b = b->next;
    }
    cur = cur->next;
  }
  cur->next = a ? a : b;
  return dummy.next;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize) {
  if (listsSize == 0)
    return NULL;

  for (int step = 1; step < listsSize; step *= 2)
    for (int i = 0; i + step < listsSize; i += 2 * step)
      lists[i] = mergeTwo(lists[i], lists[i + step]);

  return lists[0];
}
