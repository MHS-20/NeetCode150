#include "list_node.h"
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    // 1. collect every value from every list
    vector<int> vals;
    for (ListNode *head : lists)
      for (ListNode *p = head; p; p = p->next)
        vals.push_back(p->val);

    // 2. sort them
    sort(vals.begin(), vals.end());

    // 3. rebuild a new list
    ListNode dummy;
    ListNode *cur = &dummy;
    for (int v : vals) {
      cur->next = new ListNode(v);
      cur = cur->next;
    }

    return dummy.next;
  }
};
