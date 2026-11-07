#include "list_node.h"

struct ListNode *mergeTwoLists(struct ListNode *a, struct ListNode *b) {
  if (!a)
    return b;
  if (!b)
    return a;
  if (a->val <= b->val) {
    a->next = mergeTwoLists(a->next, b);
    return a;
  }
  b->next = mergeTwoLists(a, b->next);
  return b;
}
