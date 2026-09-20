# Linked Lists

## The structure

A chain of nodes, each holding a value and a pointer to the next one. The list is identified by its head; the last node points at `None`.

```
head
 ↓
[1|•]→[2|•]→[3|•]→[4|/]
```

A **doubly** linked list adds a `prev` pointer, so traversal runs both ways and a node can be removed given only a reference to itself.

```
[1|•]⇄[2|•]⇄[3|•]⇄[4]
```

## Complexity, and the one thing it buys you

| Operation | Linked list | Array |
|---|---|---|
| index `a[i]` | **O(n)** | O(1) |
| insert/delete at head | O(1) | O(n) |
| insert/delete at tail | O(1) with a tail pointer | O(1) amortised |
| insert/delete **given the node** | O(1) | O(n) |
| insert/delete given an index | O(n) — the walk dominates | O(n) |
| search | O(n) | O(n) |

The whole trade is this: an array gives O(1) access and pays O(n) to shift elements; a linked list gives O(1) splicing and pays O(n) to reach the splice point. A linked list only wins when you already hold a pointer to the node — which is why it is almost always found *inside* another structure (an LRU cache's hash map pointing into a doubly linked list, a deque's block chain) rather than used on its own.

Nodes are also individually allocated and scattered in memory, so traversal misses cache on nearly every step. An array scan of the same length is often several times faster despite identical O(n).

## Removal needs the previous node

```
delete 3:   [1|•]→[2|•]→[3|•]→[4|/]
                     └──────────↗      prev.next = node.next
```

Single-linked removal requires `prev`, which is why a **dummy head** node is worth adding whenever the head itself might be deleted — it removes the special case:

```python
dummy = ListNode(0, head)
prev, cur = dummy, head
while cur:
    if cur.val == target:
        prev.next = cur.next
    else:
        prev = cur
    cur = cur.next
return dummy.next          # correct even if the original head was removed
```

## The three techniques that cover most problems

**Two pointers at different speeds.** `slow` moves one step, `fast` two. When `fast` hits the end, `slow` is at the middle. If the list has a cycle, `fast` eventually laps `slow` and they meet — this is Floyd's cycle detection, O(n) time and O(1) space.

```
[1]→[2]→[3]→[4]→[5]
 s       s       s
 f           f       f(None)   → slow lands on 3, the middle
```

**Two pointers a fixed gap apart.** Advance `fast` by `k`, then move both until `fast` ends; `slow` sits `k` from the tail. One pass, no length count.

**Reversal by pointer rewiring.** The pattern to memorise, since it appears inside reverse-in-k-groups, palindrome checks, and reorder-list:

```python
prev, cur = None, head
while cur:
    nxt = cur.next      # save before overwriting
    cur.next = prev     # flip
    prev, cur = cur, nxt
return prev             # new head
```

O(n) time, O(1) space. Saving `nxt` first is the whole trick — overwrite `cur.next` before reading it and the rest of the list is lost.

## Pitfalls

- Losing the remainder of the list by reassigning a `next` pointer before saving it.
- Off-by-one in fast/slow: `while fast and fast.next` is the guard for a two-step advance, and whether `slow` lands on the first or second middle of an even-length list depends on where you start the pointers.
- Forgetting to terminate — a rewired tail still pointing into the list creates a cycle, and the next traversal hangs rather than crashing.
- Reaching for a linked list when an array or deque fits. In an interview it is usually the problem's *given* input, not a choice you should make.
