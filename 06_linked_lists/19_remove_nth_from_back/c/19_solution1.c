#include "list_node.h"
#include <stdlib.h>

struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
  struct ListNode dummy = {0, head};
  struct ListNode *left = &dummy;
  struct ListNode *right = &dummy;

  // create a gap of n nodes between left and right
  for (int i = 0; i < n; i++)
    right = right->next;

  // move both until right is on the last node;
  // left is then on the node before the target
  while (right->next) {
    right = right->next;
    left = left->next;
  }

  struct ListNode *target = left->next;
  left->next = target->next;
  free(target);

  return dummy.next;
}
