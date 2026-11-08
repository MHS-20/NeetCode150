# Copying a List with Extra Pointers, and the LRU Cache

Both problems on this page need a link between a node and something outside the `next` chain. Copy List with Random Pointer has to map each original node to its copy, so that pointers in the copy can be set. The LRU cache has to reach a node from its key in O(1), then move that node in O(1). A hash map gives the link in both cases, and Copy List also has an O(1)-space solution that stores the link in the list itself.

The examples follow the C++ solutions in `06_linked_lists/`. Every trace was produced by running the same steps on the input shown.

## Copy List with Random Pointer (138)

Each node has a `next` pointer and a `random` pointer, which can point to any node in the list or be null. The task is to make a **deep copy**: new nodes with the same values, whose `next` and `random` pointers point to the new nodes, never to the original ones.

The difficulty is `random`. When the copy of node A is made, the node that A's `random` points to may not have been copied yet. So the copy cannot be built in one pass, from front to back.

The examples use this list. The `random` pointers are shown by index:

```
index:    0     1     2     3     4
value:    7    13    11    10     1
random:   /     0     4     2     0
```

### Solution 1: a hash map from original to copy

**Pass 1** makes a copy of every node, with no pointers set, and records `copyOf[original] = copy`.

**Pass 2** sets the pointers of each copy by looking up the copies of the original's targets:

```cpp
copyOf[nullptr] = nullptr;                       // a null target maps to null
for (Node *cur = head; cur; cur = cur->next)
    copyOf[cur] = new Node(cur->val);
for (Node *cur = head; cur; cur = cur->next) {
    copyOf[cur]->next = copyOf[cur->next];
    copyOf[cur]->random = copyOf[cur->random];
}
return copyOf[head];
```

Pass 1 removes the order problem: by the time any pointer is set, every copy already exists. The entry `copyOf[nullptr] = nullptr` lets the last node's `next` and any null `random` go through the same lookup with no `if`.

O(n) time and O(n) extra space for the map.

### Solution 2: weaving the copies into the list

The map only answers one question: where is the copy of node X? If each copy is placed directly after its original, the answer is `X->next`, and the map is not needed.

**Pass 1, weave.** Insert each copy right after its original:

```
before:  7 → 13 → 11 → 10 → 1
after:   7 → 7' → 13 → 13' → 11 → 11' → 10 → 10' → 1 → 1'
```

**Pass 2, set `random`.** The copy of `cur` is `cur->next`, and the copy of `cur->random` is `cur->random->next`:

```cpp
for (Node *cur = head; cur; cur = cur->next->next)
    if (cur->random)
        cur->next->random = cur->random->next;
```

For node 13, whose `random` is 7: `13'->random = 7->next = 7'`.

**Pass 3, unweave.** Restore the original list's `next` pointers and link the copies to each other:

```cpp
Node *copyHead = head->next;
for (Node *cur = head; cur; cur = cur->next) {
    Node *copy = cur->next;
    cur->next = copy->next;             // original skips its copy
    if (copy->next)
        copy->next = copy->next->next;  // copy skips the next original
}
return copyHead;
```

After pass 3 the copy is `7' → 13' → 11' → 10' → 1'` with `random` values `/, 7', 1', 11', 7'`. The original is back to `7 → 13 → 11 → 10 → 1`, unchanged.

Pass 3 must restore the original list, because the caller still owns it. If it is skipped, the original list keeps the copies woven in.

O(n) time and O(1) extra space, apart from the copy itself.

## LRU Cache (146)

The task: build a cache with a fixed capacity, where `get(key)` and `put(key, value)` both run in O(1). When the cache is full and a new key is added, the **least recently used** key is removed. Both `get` and `put` count as a use.

Two structures together give O(1) for every operation:

- **A doubly linked list in order of use.** The most recently used node is at the front and the least recently used at the back. A node can be moved to the front in O(1), and the back node can be removed in O(1).
- **A hash map from key to node.** It finds the node for a key in O(1), so the list never has to be searched.

The list needs to be **doubly** linked because removing a node needs its predecessor. In a singly linked list, finding the node before a given node means walking from the head, which is O(n). With `prev` pointers, the node knows both neighbours.

The repo's solution uses two dummy nodes, `head` and `tail`, at the two ends. Every real node then has a node on each side, so `remove` and `insertFront` need no checks for an empty list or for the first and last nodes:

```
head ⇄ [most recent] ⇄ ... ⇄ [least recent] ⇄ tail
```

```cpp
void remove(Node *n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
}
void insertFront(Node *n) {
    n->prev = head;
    n->next = head->next;
    head->next->prev = n;
    head->next = n;
}
```

- **`get(key)`:** if the key is in the map, move its node to the front and return its value. Otherwise return -1.
- **`put(key, value)`:** if the key exists, update the value and move the node to the front. Otherwise, if the cache is full, remove `tail->prev`, the least recently used node, from the list and from the map. Then create the new node, add it to the map and insert it at the front.

Each node stores its key as well as its value. When the back node is removed, its key is needed to erase the map entry.

### Trace, capacity 2

The list is shown from most recent to least recent:

```
operation     result   evicted   list after
put(1, 1)                        [1]
put(2, 2)                        [2, 1]
get(1)          1                [1, 2]      1 moves to the front
put(3, 3)                 2      [3, 1]      full: 2 was at the back
get(2)         -1                [3, 1]
put(4, 4)                 1      [4, 3]
get(1)         -1                [4, 3]
get(3)          3                [3, 4]
get(4)          4                [4, 3]
```

At `put(3, 3)`, key 2 is evicted, not key 1. Both were added before 3, but `get(1)` used key 1 after key 2 was added.
