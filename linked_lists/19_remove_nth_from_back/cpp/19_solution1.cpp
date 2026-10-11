#include "list_node.h"

class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode dummy(0, head);
    ListNode *left = &dummy;
    ListNode *right = &dummy;

    if (!head || n <= 0)
      return head;

    for (int i = 0; i < n; i++)
      right = right->next;

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
