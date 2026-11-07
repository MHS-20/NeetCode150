#include "list_node.h"
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    auto cmp = [](ListNode *a, ListNode *b) { return a->val > b->val; };
    priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> minHeap(cmp);

    // seed with the head of each non-empty list
    for (ListNode *head : lists)
      if (head)
        minHeap.push(head);

    ListNode dummy;
    ListNode *cur = &dummy;

    while (!minHeap.empty()) {
      ListNode *smallest = minHeap.top();
      minHeap.pop();

      cur->next = smallest;
      cur = cur->next;

      // the only new candidate is the successor of the node we just took
      if (smallest->next)
        minHeap.push(smallest->next);
    }

    return dummy.next;
  }
};
