#include <stdlib.h>

#include "list_node.h"

// array of node pointers used as a deque (front index l, back index r)
void reorderList(struct ListNode *head) {
  if (!head || !head->next)
    return;

  // 1. store every node
  int n = 0;
  for (struct ListNode *c = head; c; c = c->next)
    n++;
  struct ListNode **nodes = malloc(n * sizeof *nodes);
  struct ListNode *curr = head;
  for (int i = 0; i < n; i++, curr = curr->next)
    nodes[i] = curr;

  // 2. relink alternating between the front and the back
  int l = 0, r = n - 1;
  struct ListNode *tail = head; // nodes[0] is already the head
  l++;
  while (l <= r) {
    tail->next = nodes[r--];
    tail = tail->next;
    if (l <= r) {
      tail->next = nodes[l++];
      tail = tail->next;
    }
  }
  tail->next = NULL;
  free(nodes);
}
