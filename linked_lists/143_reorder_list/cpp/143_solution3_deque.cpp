#include <deque>

#include "list_node.h"

class Solution {
public:
  void reorderList(ListNode *head) {
    if (!head || !head->next)
      return;

    // 1. store every node
    std::deque<ListNode *> deque;
    for (ListNode *curr = head; curr; curr = curr->next)
      deque.push_back(curr);

    // 2. relink alternating between the front and the back
    ListNode *tail = deque.front(); // the head stays first
    deque.pop_front();
    while (!deque.empty()) {
      tail->next = deque.back();
      deque.pop_back();
      tail = tail->next;
      if (!deque.empty()) {
        tail->next = deque.front();
        deque.pop_front();
        tail = tail->next;
      }
    }
    tail->next = nullptr;
  }
};
