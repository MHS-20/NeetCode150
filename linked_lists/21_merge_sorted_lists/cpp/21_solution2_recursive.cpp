#include "list_node.h"

class Solution {
public:
  ListNode *mergeTwoLists(ListNode *a, ListNode *b) {
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
};
