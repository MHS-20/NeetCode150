#include "list_node.h"

struct ListNode *reverseKGroup(struct ListNode *head, int k) {
  struct ListNode dummy = {0, head};
  struct ListNode *groupPrev = &dummy;

  for (;;) {
    // find the k-th node of this group
    struct ListNode *kth = groupPrev;
    for (int i = 0; i < k && kth; i++)
      kth = kth->next;
    if (!kth)
      break; // fewer than k nodes left

    struct ListNode *groupStart = groupPrev->next;
    struct ListNode *groupNext = kth->next; // first node after the group

    // reverse k nodes, starting with prev = groupNext so the
    // old head ends up pointing to the rest of the list
    struct ListNode *prev = groupNext;
    struct ListNode *cur = groupStart;
    while (cur != groupNext) {
      struct ListNode *next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }

    groupPrev->next = kth;  // previous part -> new group head
    groupPrev = groupStart; // old head is now the group's tail
  }

  return dummy.next;
}
