# Queues and Deques

## The queue

A queue is a FIFO line: things leave in the order they arrived. Only two operations matter.

- `push` / `enqueue` — add at the back
- `pop` / `dequeue` — remove from the front

```
       front                         back
        ↓                             ↓
pop ← [ A ][ B ][ C ][ D ] ← push
```

A stack is the same idea with one end instead of two (LIFO — last in, first out). Both restrict access on purpose: the restriction is what makes the operations cheap and the algorithm easy to reason about.

## The deque

A deque ("double-ended queue", said *deck*) allows push and pop at **both** ends.

```
push_front →  [ A ][ B ][ C ][ D ]  ← push_back
pop_front  ←                        → pop_back
```

That is the whole difference. A deque can act as a queue (push back, pop front), as a stack (push back, pop back), or as something neither can do — which is where its real value in interview problems lies.

## Why the operations are O(1)

The complexity is not a property of the *concept*, it is a property of the *implementation*. There are two standard ones.

### Doubly linked list

Each node stores a value plus pointers to its neighbours. Head and tail pointers are kept.

```
 head                                     tail
  ↓                                        ↓
[A] ⇄ [B] ⇄ [C] ⇄ [D]
```

Adding or removing at either end rewires two or three pointers. The work does not depend on how many elements are inside, so it is O(1). The cost: every element carries pointer overhead, and the nodes sit in scattered memory, so traversal is cache-hostile and indexing is O(n).

### Ring buffer (circular array)

A fixed array with two indices, `head` and `tail`, that wrap around with modulo.

```
index:   0    1    2    3    4    5
       [ _ ][ B ][ C ][ D ][ _ ][ _ ]
              ↑              ↑
            head           tail
```

Popping the front just advances `head` — the slot is abandoned, nothing is moved. When `tail` runs off the end it wraps to 0 and reuses the freed slots. When the buffer fills up, it is reallocated at double size; that single copy is O(n), but it happens so rarely that the *amortised* cost per push stays O(1). Contiguous memory means indexing is O(1) and iteration is fast.

Real implementations mix the two: CPython's `collections.deque` is a doubly linked list of fixed-size array blocks, C++'s `std::deque` is an array of pointers to fixed-size blocks.

### Why not a plain array/list

This is the mistake the data structure exists to prevent:

```python
q = [1, 2, 3, 4]
q.pop(0)        # O(n) — every remaining element shifts left one slot
```

Popping the front of a Python list (or `vector::erase(begin())` in C++) moves all `n-1` remaining elements. Inside a loop that runs `n` times, an O(n) pop turns the whole algorithm into O(n²). Use a deque and it is O(n).

## Complexity summary

| Operation | Deque | Python `list` | Linked list |
|---|---|---|---|
| push back | O(1) | O(1) amortised | O(1) |
| pop back | O(1) | O(1) | O(1) |
| push front | O(1) | **O(n)** | O(1) |
| pop front | O(1) | **O(n)** | O(1) |
| index `d[i]` | O(1)\* / O(n) | O(1) | O(n) |
| search | O(n) | O(n) | O(n) |

\* O(1) for `std::deque`; `collections.deque` is O(1) at the ends and O(n) in the middle. Never index a deque in a loop — if random access is needed, the wrong structure was chosen.

## When to reach for one

**BFS / level-order traversal.** The defining use of a queue. FIFO order is exactly what guarantees nodes are visited in order of increasing distance from the source, which is why BFS finds shortest paths in unweighted graphs.

```python
from collections import deque

def bfs(start, neighbors):
    seen = {start}
    q = deque([start])
    while q:
        node = q.popleft()          # O(1)
        for nxt in neighbors(node):
            if nxt not in seen:
                seen.add(nxt)
                q.append(nxt)
```

Process the queue one level at a time by capturing `len(q)` before the inner loop — everything currently in the queue is exactly one level.

**Monotonic deque — sliding window max/min.** The signature deque problem (LeetCode 239). Keep indices in the deque ordered so their values are decreasing. Before pushing a new index, pop from the **back** every index whose value is smaller — they can never be the maximum again, because the new element is both larger and stays in the window longer. Pop from the **front** when an index falls out of the window. The front is always the answer for the current window.

```
nums = [1, 3, -1, -3, 5], k = 3

window [1,3,-1]   deque(idx): [1, 2]   values 3, -1   → max = 3
window [3,-1,-3]  deque(idx): [1, 2, 3] values 3,-1,-3 → max = 3
window [-1,-3,5]  5 evicts everything → [4]           → max = 5
```

Each index is pushed once and popped once, so the whole scan is O(n) despite the nested `while`. This needs *both* ends, which is precisely why a queue is not enough.

**Sliding window in general.** Any window where elements leave from the left as they enter from the right.

**Fixed-size history / rate limiting.** `deque(maxlen=k)` drops from the other end automatically — the last `k` events, an *n*-frame rolling average.

**Stack.** A deque works, but if only one end is ever touched, a plain list/array is simpler and faster.

## Practical notes

- Python: `from collections import deque`. `append`/`pop` at the back, `appendleft`/`popleft` at the front. `queue.Queue` is a different thing — thread-safe with locking, much slower, only for concurrency.
- C++: `std::deque` for both ends, `std::queue` as a restricted adapter over it.
- Java: `ArrayDeque` for both queue and stack. Not `Stack` (legacy, synchronised) and usually not `LinkedList`.
- In a monotonic deque, store **indices**, not values — the window bound check needs the position.
- If a "queue" is being popped from the front with an O(n) operation, the complexity analysis is wrong, not the structure.
