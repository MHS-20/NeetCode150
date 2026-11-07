#include "list_node.h"
#include <vector>

using namespace std;

class Solution {
  ListNode *mergeTwo(ListNode *a, ListNode *b) {
    ListNode dummy;
    ListNode *cur = &dummy;
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

public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    int n = lists.size();
    if (n == 0)
      return nullptr;

    for (int step = 1; step < n; step *= 2)
      for (int i = 0; i + step < n; i += 2 * step)
        lists[i] = mergeTwo(lists[i], lists[i + step]);

    return lists[0];
  }
};
