#include <stack>

#include "list_node.h"

class Solution {
public:
  void reorderList(ListNode *head) {
    if (!head || !head->next)
      return;

    // 1. find the end of the first half
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
      slow = slow->next;
      fast = fast->next->next;
    }

    // 2. cut the list and push the second half onto a stack
    std::stack<ListNode *> stack;
    for (ListNode *curr = slow->next; curr; curr = curr->next)
      stack.push(curr);
    slow->next = nullptr; // split into two lists

    // 3. merge: popping the stack yields the second half in reverse
    ListNode *first = head;
    while (!stack.empty()) {
      ListNode *second = stack.top();
      stack.pop();
      second->next = first->next;
      first->next = second;
      first = second->next;
    }
  }
};
