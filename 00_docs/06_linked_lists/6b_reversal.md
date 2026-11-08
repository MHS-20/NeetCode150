# Reversing a Linked List in Place

Reversing a list means making every `next` pointer point to the node before it, so that the old last node becomes the head. Done in place, it needs O(1) extra memory: three pointers move along the list and flip one link per step. The same loop is used as a step inside other problems. Reverse Nodes in k-Group reverses one group at a time, and Reorder List reverses the second half of the list ([reorder and merge](6c_reorder_and_merge.md)).

The examples follow the C++ solutions in `06_linked_lists/`. Every trace was produced by running the same steps on the input shown.

## Reverse Linked List (206), iterative

Three pointers walk the list:

- `prev`: the head of the part already reversed. It starts as null.
- `cur`: the node whose link is flipped in this step.
- `next`: the node after `cur`, saved before the link is overwritten.

```cpp
ListNode *prev = nullptr, *cur = head;
while (cur) {
    ListNode *next = cur->next;   // 1. save the rest of the list
    cur->next = prev;             // 2. flip the link
    prev = cur;                   // 3. move prev forward
    cur = next;                   // 4. move cur forward
}
return prev;                      // the new head
```

Step 1 has to come before step 2. Once `cur->next` is overwritten, `next` is the only pointer to the rest of the list.

### Trace on `1 → 2 → 3`

At every point the list is split in two: a reversed part starting at `prev`, and an untouched part starting at `cur`. Each step moves one node from the second part to the front of the first.

```
start
    prev = /        cur
                     ↓
                    [1]→[2]→[3]→/

step 1: next = 2, then 1->next = prev (null)
         prev       cur
          ↓          ↓
    / ←[1]          [2]→[3]→/

step 2: next = 3, then 2->next = 1
              prev  cur
               ↓     ↓
    / ←[1]←[2]      [3]→/

step 3: next = null, then 3->next = 2
                   prev     cur = /
                    ↓
    / ←[1]←[2]←[3]
```

`cur` is null, so the loop ends. `prev` points to 3, the new head, and the list reads `3 → 2 → 1`.

The loop runs once per node: O(n) time and O(1) extra space.

## Reverse Linked List (206), recursive

The repo's second solution reverses the rest of the list first, then attaches the current node at its end:

```cpp
ListNode *reverseList(ListNode *head) {
    if (!head || !head->next)
        return head;                         // 0 or 1 node: already reversed
    ListNode *newHead = reverseList(head->next);
    head->next->next = head;                 // the old next node now points back
    head->next = nullptr;                    // head becomes the tail
    return newHead;
}
```

After the recursive call on `2 → 3`, the list looks like this. Node 1 still points to 2, and 2 is now the tail of the reversed part:

```
[1]→[2]←[3]          newHead = 3
     ↓
     /
```

`head->next->next = head` makes 2 point back to 1, and `head->next = nullptr` ends the list at 1:

```
/ ←[1]←[2]←[3]       newHead = 3
```

The new head is the old last node, found at the bottom of the recursion and passed back up unchanged. This version is O(n) time, but it uses one stack frame per node, so O(n) space instead of O(1).

## Reverse Nodes in k-Group (25)

The task: reverse the nodes of the list `k` at a time. If fewer than `k` nodes remain at the end, they stay as they are. For `[1, 2, 3, 4, 5]` and `k = 2`, the result is `[2, 1, 4, 3, 5]`.

Each group is reversed with the loop above, but two links outside the group also have to change:

- the node **before** the group has to point to the group's new first node;
- the group's new last node has to point to the node **after** the group.

### The pointers

```
groupPrev    groupStart              kth     groupNext
    ↓            ↓                    ↓          ↓
  [ .. ]  →    [ a ]  →  ...  →     [ b ]  →  [ .. ]
             └──────── k nodes ────────┘
```

- `groupPrev`: the node just before the group. For the first group this is the dummy head.
- `groupStart`: the group's first node. It becomes the group's last node.
- `kth`: the group's `k`th node. It becomes the group's first node.
- `groupNext`: the first node after the group.

### The iterative solution

```cpp
ListNode dummy(0, head);
ListNode *groupPrev = &dummy;
for (;;) {
    ListNode *kth = groupPrev;
    for (int i = 0; i < k && kth; i++)
        kth = kth->next;
    if (!kth)
        break;                             // fewer than k nodes left

    ListNode *groupStart = groupPrev->next;
    ListNode *groupNext = kth->next;

    ListNode *prev = groupNext, *cur = groupStart;
    while (cur != groupNext) {             // reverse the k nodes
        ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    groupPrev->next = kth;                 // link the node before the group
    groupPrev = groupStart;                // the old first node is the new last
}
return dummy.next;
```

The reversal starts with `prev = groupNext` instead of null. The first node flipped is `groupStart`, so its `next` becomes `groupNext`. That joins the end of the reversed group to the rest of the list with no extra step.

### Trace on `[1, 2, 3, 4, 5]`, `k = 2`

```
group 1:  groupPrev = dummy, groupStart = 1, kth = 2, groupNext = 3

  before:   dummy → 1 → 2 → 3 → 4 → 5
  reverse:  1->next = 3, then 2->next = 1
  link:     dummy->next = 2
  after:    dummy → 2 → 1 → 3 → 4 → 5          groupPrev = 1

group 2:  groupPrev = 1, groupStart = 3, kth = 4, groupNext = 5

  reverse:  3->next = 5, then 4->next = 3
  link:     1->next = 4
  after:    dummy → 2 → 1 → 4 → 3 → 5          groupPrev = 3

group 3:  only node 5 is left, so kth becomes null: stop
```

The result is `[2, 1, 4, 3, 5]`. Every node is visited a constant number of times, once to find `kth` and once to reverse it, so the whole pass is O(n) with O(1) extra space.

### The recursive solution

The repo's second solution checks that `k` nodes exist, reverses the rest of the list recursively first, and then reverses the current group with `prev` starting at the already-processed rest:

```cpp
ListNode *node = head;
for (int i = 0; i < k; i++) {
    if (!node) return head;                // fewer than k nodes: unchanged
    node = node->next;
}
ListNode *prev = reverseKGroup(node, k);   // the rest, already processed
ListNode *cur = head;
for (int i = 0; i < k; i++) {              // reverse this group onto it
    ListNode *next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
}
return prev;
```

The idea of starting `prev` at the rest of the list is the same as in the iterative version. This version needs no `groupPrev`, because each call returns the new first node of its group and the caller links it in. It uses one stack frame per group, O(n/k) space.
