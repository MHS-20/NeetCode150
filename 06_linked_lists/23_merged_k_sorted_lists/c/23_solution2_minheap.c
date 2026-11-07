#include "list_node.h"
#include <stdlib.h>

// array-backed binary min-heap of node pointers keyed on val
static void sift_up(struct ListNode **h, int i) {
  while (i > 0) {
    int parent = (i - 1) / 2;
    if (h[parent]->val <= h[i]->val)
      break;
    struct ListNode *t = h[parent];
    h[parent] = h[i];
    h[i] = t;
    i = parent;
  }
}

static void sift_down(struct ListNode **h, int size, int i) {
  for (;;) {
    int smallest = i, l = 2 * i + 1, r = l + 1;
    if (l < size && h[l]->val < h[smallest]->val)
      smallest = l;
    if (r < size && h[r]->val < h[smallest]->val)
      smallest = r;
    if (smallest == i)
      return;
    struct ListNode *t = h[smallest];
    h[smallest] = h[i];
    h[i] = t;
    i = smallest;
  }
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize) {
  struct ListNode **heap = malloc((listsSize > 0 ? listsSize : 1) * sizeof(*heap));
  int size = 0;

  // seed with the head of each non-empty list
  for (int i = 0; i < listsSize; i++) {
    if (lists[i]) {
      heap[size] = lists[i];
      sift_up(heap, size++);
    }
  }

  struct ListNode dummy;
  struct ListNode *cur = &dummy;

  while (size > 0) {
    struct ListNode *smallest = heap[0];

    cur->next = smallest;
    cur = cur->next;

    // replace the root with its successor (or the last node) and restore order
    heap[0] = smallest->next ? smallest->next : heap[--size];
    sift_down(heap, size, 0);
  }

  free(heap);
  cur->next = NULL;
  return dummy.next;
}
