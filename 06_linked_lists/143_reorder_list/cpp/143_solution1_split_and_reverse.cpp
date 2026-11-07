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

    // 2. cut the list
    ListNode *prev = nullptr;
    ListNode *curr = slow->next;
    slow->next = nullptr;

    // reverse the second half
    while (curr) {
      ListNode *next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    ListNode *second = prev; // head of reversed second half

    // 3. merge: alternate nodes from first and second
    ListNode *first = head;
    while (second) {
      ListNode *next1 = first->next;
      ListNode *next2 = second->next;

      first->next = second;
      second->next = next1;

      first = next1;
      second = next2;
    }
  }
};
