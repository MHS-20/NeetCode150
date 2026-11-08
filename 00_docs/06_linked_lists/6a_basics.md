# Linked Lists: Structure, Dummy Heads and Gap Pointers

A linked list stores each element in its own node, and each node points to the next one. Linked list problems are mostly about changing those pointers in the right order: a pointer overwritten too early loses the rest of the list, and a node removed without its predecessor leaves the list broken. Two tools handle most of these problems: a **dummy head**, which removes the special case of the first node, and **two pointers** a fixed distance apart.

The examples follow the C++ solutions in `06_linked_lists/`. Every trace was produced by running the same steps on the input shown.

## The structure

Each node holds a value and a pointer to the next node. The list is reached through a pointer to its first node, the **head**. The last node's `next` is null, written `/` below.

```
head
 ↓
[1|•]→[2|•]→[3|•]→[4|/]
```

```cpp
struct ListNode {
    int val;
    ListNode *next;
};
```

A **doubly linked** list also stores a `prev` pointer in each node. A node can then be removed with only a pointer to that node, because it can reach both of its neighbours:

```
/ ←[1]⇄[2]⇄[3]⇄[4]→ /
```

## What a linked list costs

| Operation | Linked list | Array |
|---|---|---|
| read element `i` | O(n): walk from the head | O(1) |
| insert or remove at the head | O(1) | O(n): shift every element |
| insert or remove after a node already held | O(1) | O(n) |
| insert or remove at position `i` | O(n): the walk to `i` | O(n) |
| search for a value | O(n) | O(n) |

A linked list only does better than an array when the code already has a pointer to the node next to the change. That is why it is often used inside another structure that provides the pointer. The LRU cache in [copy and cache](6d_copy_and_cache.md#lru-cache-146) keeps a hash map from each key to its node.

The nodes are allocated one by one, so they are not next to each other in memory. An array scan reads consecutive memory, which the CPU cache loads in blocks. A linked list walk follows pointers to scattered addresses and gets less help from the cache, so it is usually slower than an array scan of the same length, even though both are O(n).

## Removing a node needs the node before it

In a singly linked list, removing node `3` means changing the `next` pointer of node `2`, the node **before** it:

```
before:   [1|•]→[2|•]→[3|•]→[4|/]

          prev.next = prev.next.next

after:    [1|•]→[2|•]────────→[4|/]
                       [3|•]↗          node 3 is no longer reachable
```

When the node to remove is the head, there is no node before it. The code then needs a separate case that changes the head pointer instead.

### The dummy head

A **dummy head** is an extra node placed in front of the real head. Every real node, including the first, now has a node before it, so one piece of code handles every position. At the end, the real list starts at `dummy.next`:

```
dummy
 ↓
[0|•]→[1|•]→[2|•]→[3|•]→[4|/]
       ↑
       real head = dummy.next
```

In C++ the repo's solutions declare the dummy as a local variable, `ListNode dummy(0, head);`. It is on the stack, so it needs no `new` or `delete`, and the function returns `dummy.next`, never `&dummy`.

The dummy head also helps when **building** a list. Merge Two Sorted Lists and Add Two Numbers keep a `tail` pointer that starts at the dummy and append each new node with `tail->next = node; tail = tail->next;`. Without the dummy, the first append would need its own case to set the head.

## Remove Nth Node From End of List (19): pointers a fixed gap apart

The task: remove the `n`th node counted from the end. The length of the list is not given.

Counting the length first and then walking again works, but takes two passes. One pass is enough with two pointers kept `n` nodes apart. When the front pointer reaches the last node, the back pointer is just before the node to remove.

```cpp
ListNode dummy(0, head);
ListNode *left = &dummy, *right = &dummy;
for (int i = 0; i < n; i++)
    right = right->next;          // open a gap of n nodes
while (right->next) {             // stop when right is on the last node
    right = right->next;
    left = left->next;
}
left->next = left->next->next;    // remove the node after left
return dummy.next;
```

Both pointers start at the dummy. That way, when `n` equals the length of the list, `left` stays on the dummy and the real head is removed with no special case.

For `[1, 2, 3, 4, 5]` and `n = 2`, the node to remove is 4:

```
after the gap:   left = dummy   right = 2
step 1:          left = 1       right = 3
step 2:          left = 2       right = 4
step 3:          left = 3       right = 5      right->next is null: stop

left is 3, so 3->next skips 4:   [1, 2, 3, 5]
```

The gap stays at `n` nodes the whole time. When `right` is on the last node, `left` is `n` nodes before it, which is the node just before the `n`th from the end.

## Merge Two Sorted Lists (21)

The task: merge two sorted lists into one sorted list, reusing their nodes.

The solution keeps a `tail` pointer to the last node of the merged list. At each step it takes the smaller of the two front nodes, links it after `tail`, and moves forward in that list:

```cpp
ListNode dummy;
ListNode *tail = &dummy;
while (list1 && list2) {
    if (list1->val <= list2->val) {
        tail->next = list1;
        list1 = list1->next;
    } else {
        tail->next = list2;
        list2 = list2->next;
    }
    tail = tail->next;
}
tail->next = list1 ? list1 : list2;   // the rest is already sorted
return dummy.next;
```

For `list1 = [1, 2, 4]` and `list2 = [1, 3, 4]`:

```
list1 front  list2 front   takes          merged so far
     1            1        list1's 1      1
     2            1        list2's 1      1 1
     2            3        2              1 1 2
     4            3        3              1 1 2 3
     4            4        list1's 4      1 1 2 3 4
     —            4        list1 empty: attach the rest of list2
                                          1 1 2 3 4 4
```

When one list runs out, the other is linked on in one step. Its remaining nodes are already sorted and already linked to each other, so there is nothing to copy.

Taking from `list1` when the values are equal (`<=`) keeps equal values in their original order: the first list's copy comes first. A merge with this property is called **stable**.

The repo's second solution is recursive: the smaller head node is returned, with its `next` set to the merge of the rest. It is shorter, but uses one stack frame per node, so a list of 10 000 nodes needs 10 000 nested calls.

## Fast and slow pointers

A pointer that moves one node per step and another that moves two find the middle of a list in one pass, and detect a cycle. Both are covered in [Floyd's cycle detection](../08_techniques/8g_floyd_cycle_detection.md). Linked List Cycle (141) and Find the Duplicate Number (287) are covered there. The middle of a list is also the first step of Reorder List in [reorder and merge](6c_reorder_and_merge.md).

## Common mistakes

- **Overwriting a `next` pointer before saving it.** After `cur->next = prev`, the old `cur->next` is gone. If no other pointer held it, the rest of the list is lost. Save it first: `ListNode *next = cur->next;`.
- **Dereferencing null.** Every `p->next` needs `p` to be non-null, and every `p->next->next` needs `p->next` to be non-null too. Loop conditions such as `while (fast->next && fast->next->next)` check both before moving.
- **Leaving a cycle behind.** If the node that should be the new tail still points into the list, the list becomes a cycle. The next traversal loops forever instead of crashing, so the error is hard to see. After splitting or reordering, set the new tail's `next` to null.
- **Returning the dummy.** The real list starts at `dummy.next`.
