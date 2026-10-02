#include "list_node.h"

class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode dummy(0, head);
    ListNode *left = &dummy;
    ListNode *right = &dummy;

    // create a gap of n nodes between left and right
    for (int i = 0; i < n; i++)
      right = right->next;

    // move both until right is on the last node;
    // left is then on the node before the target
    while (right->next) {
      right = right->next;
      left = left->next;
    }

    ListNode *target = left->next;
    left->next = target->next;
    delete target;

    return dummy.next;
  }
};
