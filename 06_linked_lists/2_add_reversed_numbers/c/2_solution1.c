#include "list_node.h"
#include <stdlib.h>

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
  struct ListNode dummy = {0, NULL};
  struct ListNode *tail = &dummy;
  int carry = 0;

  while (l1 || l2 || carry) {
    int sum = carry;
    if (l1) {
      sum += l1->val;
      l1 = l1->next;
    }
    if (l2) {
      sum += l2->val;
      l2 = l2->next;
    }

    carry = sum / 10;
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = sum % 10;
    node->next = NULL;
    tail->next = node;
    tail = node;
  }

  return dummy.next;
}
