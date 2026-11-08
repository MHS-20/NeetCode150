# Reordering and Merging Linked Lists

These problems rebuild a list in a new order from its existing nodes, or build one list out of several. They put together the pieces from [basics](6a_basics.md) and [reversal](6b_reversal.md): finding the middle, reversing part of a list, and merging two lists with a `tail` pointer behind a dummy head.

The examples follow the C++ solutions in `06_linked_lists/`. Every trace was produced by running the same steps on the input shown.

## Reorder List (143)

The task: rearrange `L0 → L1 → … → Ln` into `L0 → Ln → L1 → Ln-1 → L2 → …`, in place. For `[1, 2, 3, 4, 5]` the result is `[1, 5, 2, 4, 3]`.

The new order takes nodes alternately from the front and from the back. A singly linked list can only be walked forwards, so the back half is reversed first, after which both halves can be walked forwards. The solution has three steps.

### Step 1: find the end of the first half

`slow` moves one node per step and `fast` two. The loop stops when `fast` cannot move two more nodes:

```cpp
ListNode *slow = head, *fast = head;
while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
}
```

`slow` ends on the last node of the first half. For 5 nodes it stops on node 3, and for 4 nodes on node 2. With an odd length the first half gets the extra node.

```
1 → 2 → 3 → 4 → 5          1 → 2 → 3 → 4
        ↑                       ↑
       slow                    slow
```

### Step 2: cut the list and reverse the second half

`slow->next = nullptr` ends the first half at `slow`. Then the second half is reversed with the loop from [reversal](6b_reversal.md):

```
first:   1 → 2 → 3 → /
second:  5 → 4 → /                (was 4 → 5)
```

### Step 3: merge the two halves alternately

Each step takes one node from each half. Both `next` pointers are saved before either is overwritten:

```cpp
ListNode *first = head;
while (second) {
    ListNode *next1 = first->next;
    ListNode *next2 = second->next;
    first->next = second;      // first → second
    second->next = next1;      // second → the old next of first
    first = next1;
    second = next2;
}
```

For `first = 1 → 2 → 3` and `second = 5 → 4`:

```
start:     first = 1, second = 5
step 1:    1 → 5 → 2 → 3          first = 2, second = 4
step 2:    1 → 5 → 2 → 4 → 3      first = 3, second = null: stop
```

The second half never has more nodes than the first, so the loop stops when `second` runs out. The last node of the first half, 3, keeps the null `next` from step 2, so the list ends there.

All three steps are O(n), and the whole solution uses O(1) extra space.

### The other two solutions

- **Stack.** After step 1, push the nodes of the second half onto a stack. Popping returns them last to first, which replaces the reversal. O(n) time and O(n) space for the stack.
- **Deque.** Push every node into a deque, then link nodes taken alternately from the front and the back. It needs no middle and no reversal, and it ends by setting the last node's `next` to null. O(n) time and O(n) space.

Both are shorter to get right. The split-and-reverse version is the only one with O(1) extra space.

## Add Two Numbers (2)

The task: two non-negative numbers are stored as lists of digits, **least significant digit first**. Return their sum in the same form.

Storing the lowest digit first matches the order of hand addition, which starts from the ones column. The solution walks both lists together, adds the two digits and the carry, appends the last digit of that sum, and carries the rest:

```cpp
ListNode dummy;
ListNode *tail = &dummy;
int carry = 0;
while (l1 || l2 || carry) {
    int sum = carry;
    if (l1) { sum += l1->val; l1 = l1->next; }
    if (l2) { sum += l2->val; l2 = l2->next; }
    carry = sum / 10;
    tail->next = new ListNode(sum % 10);
    tail = tail->next;
}
return dummy.next;
```

For `l1 = [2, 4, 3]` (342) and `l2 = [5, 6, 4]` (465):

```
digits     carry in   sum   new digit   carry out
2 + 5         0         7       7           0
4 + 6         0        10       0           1
3 + 4         1         8       8           0
```

The result is `[7, 0, 8]`, which is 807.

The loop condition includes `carry`. For `[9, 9] + [1]` (99 + 1), both lists run out while the carry is still 1, and that last pass adds the extra digit: `[0, 0, 1]`, which is 100. A missing node in one list counts as 0, so lists of different lengths need no separate case.

## Merge k Sorted Lists (23)

The task: merge `k` sorted lists into one sorted list. `N` is the total number of nodes.

The repo has three solutions.

### Solution 1: collect and sort

Copy every value into an array, sort the array, and build a new list from it. O(N log N) time and O(N) space, and it allocates `N` new nodes instead of reusing the old ones. It does not use the fact that the lists are already sorted.

### Solution 2: a min-heap of list fronts

The next node of the merged list is always the smallest of the `k` current front nodes. A min-heap keeps those fronts. Each step pops the smallest node, appends it, and pushes that node's successor, the only new front:

```cpp
for (ListNode *head : lists)
    if (head) minHeap.push(head);
while (!minHeap.empty()) {
    ListNode *smallest = minHeap.top();
    minHeap.pop();
    cur->next = smallest;
    cur = cur->next;
    if (smallest->next)
        minHeap.push(smallest->next);
}
```

The heap never holds more than `k` nodes, so each push and pop costs O(log k). Every node is pushed and popped once, for O(N log k) time and O(k) extra space. Heaps are covered in [heaps](../02_data_structures/2e_heaps_and_priority_queues.md).

### Solution 3: merge in pairs

Merge list 0 with list 1, list 2 with list 3, and so on, using Merge Two Sorted Lists ([basics](6a_basics.md#merge-two-sorted-lists-21)). Then merge the results in pairs again, until one list remains:

```cpp
for (int step = 1; step < n; step *= 2)
    for (int i = 0; i + step < n; i += 2 * step)
        lists[i] = mergeTwo(lists[i], lists[i + step]);
return lists[0];
```

For five lists `[1,4,5]`, `[1,3,4]`, `[2,6]`, `[0]` and `[7]`:

```
step 1:  0+1 → [1,1,3,4,4,5]    2+3 → [0,2,6]      4 alone → [7]
step 2:  0+2 → [0,1,1,2,3,4,4,5,6]                 4 alone → [7]
step 4:  0+4 → [0,1,1,2,3,4,4,5,6,7]
```

Each round merges every node once, which costs O(N). The number of lists halves every round, so there are about log₂ k rounds, for O(N log k) time in total, the same as the heap. Merging in place needs O(1) extra space.

Merging the lists one after another into a single growing result also works, but costs O(N · k) in the worst case. The first list's nodes are walked again in every one of the `k - 1` merges.
