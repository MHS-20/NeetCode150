#include "list_node.h"

struct ListNode *reverseList(struct ListNode *head) {
  struct ListNode *prev = NULL;
  struct ListNode *cur = head;

  while (cur != NULL) {
    struct ListNode *next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }

  return prev;
}
