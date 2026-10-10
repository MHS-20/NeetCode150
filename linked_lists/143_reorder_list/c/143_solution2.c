#include <stdlib.h>

#include "list_node.h"

void reorderList(struct ListNode *head) {
  if (!head || !head->next)
    return;

  // 1. find the end of the first half
  struct ListNode *slow = head, *fast = head;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  // 2. cut the list and push the second half onto a stack
  int n = 0;
  for (struct ListNode *c = slow->next; c; c = c->next)
    n++;
  struct ListNode **stack = malloc(n * sizeof *stack);
  int top = 0;

  struct ListNode *curr = slow->next;
  slow->next = NULL; // split into two lists
  while (curr) {
    stack[top++] = curr;
    curr = curr->next;
  }

  // 3. merge: popping the stack yields the second half in reverse
  struct ListNode *first = head;
  while (top > 0) {
    struct ListNode *second = stack[--top];
    second->next = first->next;
    first->next = second;
    first = second->next;
  }
  free(stack);
}
