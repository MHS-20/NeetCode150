#include "node.h"
#include <stdlib.h>

struct Node *copyRandomList(struct Node *head) {
  if (!head)
    return NULL;

  // pass 1: interleave copies
  for (struct Node *cur = head; cur; cur = cur->next->next) {
    struct Node *copy = malloc(sizeof(struct Node));
    copy->val = cur->val;
    copy->random = NULL;
    copy->next = cur->next;
    cur->next = copy;
  }

  // pass 2: set random pointers
  for (struct Node *cur = head; cur; cur = cur->next->next) {
    if (cur->random)
      cur->next->random = cur->random->next;
  }

  // pass 3: separate the lists
  struct Node *copyHead = head->next;
  for (struct Node *cur = head; cur; cur = cur->next) {
    struct Node *copy = cur->next;
    cur->next = copy->next;
    if (copy->next)
      copy->next = copy->next->next;
  }

  return copyHead;
}
