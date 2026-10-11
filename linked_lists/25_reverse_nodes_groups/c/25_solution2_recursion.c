#include "list_node.h"

struct ListNode *reverseKGroup(struct ListNode *head, int k) {
  // check that k nodes exist
  struct ListNode *node = head;
  for (int i = 0; i < k; i++) {
    if (!node)
      return head; // fewer than k: leave as is
    node = node->next;
  }
  // node is now the (k+1)-th node, i.e. the start of the rest

  struct ListNode *prev = reverseKGroup(node, k); // already-processed rest
  struct ListNode *cur = head;
  for (int i = 0; i < k; i++) {
    struct ListNode *next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  return prev; // new head of this group
}
