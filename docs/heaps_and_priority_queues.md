# Heaps and Priority Queues

## Two names, one thing

A **priority queue** is the interface: a collection where you insert items freely and always remove the one with the highest priority, not the one that arrived first. A **heap** is the data structure that implements it efficiently. In interview conversation the two words are used interchangeably; in a language's standard library, one is usually the class name and the other the underlying array.

The operations that matter:

- `push(x)` — insert, O(log n)
- `pop()` — remove and return the top, O(log n)
- `peek()` / `top()` — read the top without removing it, O(1)

A **min-heap** keeps the smallest element at the top. A **max-heap** keeps the largest.

## The shape and the invariant

A heap is a **complete** binary tree — every level full except the last, which fills left to right — obeying the **heap property**: every parent compares favourably to both of its children. In a min-heap, `parent ≤ both children`.

```
min-heap                     max-heap
        1                          10
      /   \                      /    \
     3     5                    8      9
    / \   /                    / \    /
   4   8 9                    4   3  5
```

Two things follow from the invariant that catch people out:

**The top is the only element you know anything about.** A heap is not sorted. In the min-heap above, 8 sits at level 2 while 9 sits at level 2 as well, and 5 is above both — there is no left-to-right order at all, only the vertical parent-child relation. Printing the backing array gives `[1, 3, 5, 4, 8, 9]`, which is not ascending and is not supposed to be.

**Searching is O(n).** With no ordering between siblings or between subtrees, finding an arbitrary value means scanning everything. If you need "is x in here" as well as "give me the minimum", a heap alone is the wrong structure — pair it with a hash set, or use a balanced BST / `TreeMap` / `std::set`.

## Why the operations are log n

Completeness is what makes the height exactly `⌊log₂ n⌋`. A complete tree cannot be skewed; there are no gaps to distort it. Every push and pop walks one root-to-leaf path, so the cost is the height.

**Push — sift up.** Append the new element at the next free slot (the end of the array), then swap it with its parent while it violates the invariant.

```
insert 2 into min-heap [1, 3, 5, 4, 8, 9]

        1                1                  1
      /   \            /   \              /   \
     3     5    →     3     5      →     3     2
    / \   / \        / \   / \          / \   / \
   4   8 9   2      4   8 9   2        4   8 9   5
                      2 < 5, swap        2 > 1, stop
```

At most `log n` swaps, one per level.

**Pop — sift down.** The top is the answer, but removing it leaves a hole at the root. Move the *last* element into the root (keeping the tree complete) and swap it downward with its smaller child until the invariant holds.

```
pop from [1, 3, 5, 4, 8, 9]

        1          9 moves up        9              3
      /   \         to root        /   \          /   \
     3     5    →              →  3     5    →   4     5
    / \   /                      / \            / \
   4   8 9                      4   8          9   8
                                3 < 5, swap    4 < 9, swap
```

Again one comparison-and-swap per level, so O(log n). Moving the *last* element rather than promoting a child is what keeps the tree complete; promoting a child would leave a hole in the middle of a level.

## The array layout

A heap is stored as a flat array, never as linked nodes. Completeness guarantees no gaps, so the tree structure is pure arithmetic:

```
index:    0    1    2    3    4    5
        [ 1 ][ 3 ][ 5 ][ 4 ][ 8 ][ 9 ]

left(i)   = 2i + 1
right(i)  = 2i + 2
parent(i) = (i − 1) // 2
```

No pointer overhead per element, contiguous memory, and sift-up/sift-down walk memory in a predictable pattern. This is why a heap beats a balanced BST in practice for priority-queue work even though both are O(log n) on paper.

## Building a heap from n elements: O(n), not O(n log n)

Pushing `n` elements one at a time costs O(n log n). Heapifying an existing array costs O(n) — run sift-down on every non-leaf node, starting from the last one and working backwards to the root.

```python
import heapq
heapq.heapify(arr)     # O(n), in place
```

The reason the naive bound is loose: sift-down from a node costs its *height*, and almost every node is near the bottom where the height is tiny. Half the nodes are leaves with height 0 and cost nothing; a quarter have height 1; an eighth have height 2. Summing,

```
n/2 · 0  +  n/4 · 1  +  n/8 · 2  +  n/16 · 3  + ...  =  n · Σ (k / 2^(k+1))  =  n
```

The series converges to 1, so the total is O(n). Only the single root pays the full `log n`. Sift-*up* has the opposite profile — the expensive case is the common one, which is why insert-one-at-a-time does not get the same discount.

## Complexity summary

| Operation | Cost | Note |
|---|---|---|
| `peek` | O(1) | array index 0 |
| `push` | O(log n) | sift up |
| `pop` | O(log n) | sift down |
| `heapify` an array | O(n) | see above |
| search arbitrary value | O(n) | no ordering to exploit |
| delete arbitrary element | O(log n) | only with an index map; O(n) without |
| heapsort (pop everything) | O(n log n) | in place, no extra memory |

Space is O(n) for the array and nothing else.

## Picking the right heap for "top K" problems

### The counterintuitive part

For the **K largest** elements you use a **min-heap**. For the **K smallest** you use a **max-heap**. The fix for the confusion is to stop asking which heap matches the thing you want, and start asking which heap makes it cheap to find the thing you want to throw away.

### The principle

The heap holds your current best K candidates. As new elements arrive, some should replace the weakest candidate already in the set. So the question that decides the heap type is:

> Of the K elements currently kept, which is the weakest — the first one I would evict?

Keeping the **K largest**: the weakest kept element is the **smallest** of them. You need O(1) access to "the smallest of my current K" in order to compare it against each arriving element and evict it when the newcomer is bigger. That is a **min-heap's** top.

Keeping the **K smallest**: the weakest kept element is the **largest** of them. That is a **max-heap's** top.

The heap type is chosen by what you evict, not by what you are ultimately looking for. The top is always the next one on the chopping block.

### The algorithm, identical in both cases

```
heap = empty        # min-heap for "K largest", max-heap for "K smallest"

for x in input:
    if len(heap) < K:
        push x
    elif x is better than heap.top():     # larger for K-largest, smaller for K-smallest
        pop()                             # discard the weakest survivor
        push x

# heap now holds exactly the K largest (or K smallest)
```

### Worked example — K largest with a min-heap

Three largest values in `[5, 1, 9, 3, 10, 2, 8]`:

```
K = 3, min-heap starts empty

push 5                                    heap {5}
push 1                                    heap {1, 5}
push 9                                    heap {1, 5, 9}      size == K
x = 3:   top 1,  3 > 1   pop 1, push 3    heap {3, 5, 9}
x = 10:  top 3,  10 > 3  pop 3, push 10   heap {5, 9, 10}
x = 2:   top 5,  2 < 5   skip             heap {5, 9, 10}
x = 8:   top 5,  8 > 5   pop 5, push 8    heap {8, 9, 10}

result {8, 9, 10}
```

The heap's own minimum, sitting at its top, is exactly the value most in danger of being replaced.

### Worked example — K smallest with a max-heap

Three smallest values in the same array:

```
K = 3, max-heap starts empty

push 5                                    heap {5}
push 1                                    heap {1, 5}
push 9                                    heap {1, 5, 9}      size == K
x = 3:   top 9,  3 < 9   pop 9, push 3    heap {1, 3, 5}
x = 10:  top 5,  10 < 5? no, skip         heap {1, 3, 5}
x = 2:   top 5,  2 < 5   pop 5, push 2    heap {1, 2, 3}
x = 8:   top 3,  8 < 3? no, skip          heap {1, 2, 3}

result {1, 2, 3}
```

### Why not an unbounded heap of the matching type

Pushing all N elements into a min-heap and popping K times does give the K smallest. It costs O(N) to heapify plus O(K log N) to extract, and O(N) space. The bounded opposite-type heap costs **O(N log K)** time and **O(K)** space: every element does at most one push and one pop against a heap that never grows past K. When K is much smaller than N — the usual shape of these problems — that is a genuine asymptotic win, and the memory difference matters when the input is a stream that does not fit in RAM.

### Quick reference

| You want to keep | The loser to evict is the | Heap type | Compare with |
|---|---|---|---|
| K largest | smallest of the K kept | min-heap | `if x > heap.top()` |
| K smallest | largest of the K kept | max-heap | `if x < heap.top()` |

### The question to ask when you freeze up

> "What am I keeping, and when I need to make room, which of my kept elements loses first?"

The property identifying the loser names the heap that gives O(1) access to it.

## Other recurring uses

**Merge K sorted lists.** Hold one element from each list in a min-heap of size K. Pop the global minimum, then push the next element from whichever list it came from. O(N log K) for N total elements, against O(N·K) for repeatedly scanning all K heads.

**Running median — two heaps.** A max-heap for the lower half, a min-heap for the upper half, kept within one element of the same size. The median is the top of the larger heap, or the average of the two tops when sizes are equal. Both tops are O(1), and rebalancing after each insert is O(log n). The two heaps face each other, so the two elements adjacent to the median are always exposed.

```
lower (max-heap)        upper (min-heap)
   [1, 3, 4]      |        [6, 8, 9]
         ↑ top         top ↑
        median = (4 + 6) / 2
```

**Dijkstra and A\*.** A min-heap keyed by tentative distance supplies the next-closest unvisited node. This is where the "decrease-key" question arises; see the lazy-deletion note below.

**Task scheduling, event simulation, rate limiting.** Anything where the next thing to process is chosen by a computed priority rather than arrival order — Task Scheduler, meeting rooms, CPU interval problems.

**Kth largest in a stream.** A bounded min-heap of size K, where the top *is* the running answer after each insert.

## Language notes

**Python** has `heapq`, which is a **min-heap only**, operating on a plain list.

```python
import heapq

h = []
heapq.heappush(h, 5)
smallest = h[0]              # peek, O(1)
smallest = heapq.heappop(h)
heapq.heapify(arr)           # in place, O(n)
heapq.heappushpop(h, x)      # push then pop, one sift — cheaper than doing both
heapq.nlargest(k, arr)       # does the bounded-heap trick for you
```

For a max-heap, negate on the way in and on the way out:

```python
heapq.heappush(h, -x)
largest = -heapq.heappop(h)
```

Negation fails on non-numeric items, so for objects push a tuple `(priority, tiebreaker, item)`. Python compares tuples element by element, and it will try to compare the third field if the first two tie — include a monotonic counter as the tiebreaker when the items themselves are not comparable, or the push raises `TypeError` on a collision.

**C++**: `std::priority_queue` is a **max-heap** by default; `std::priority_queue<int, vector<int>, greater<int>>` gives a min-heap. **Java**: `PriorityQueue` is a min-heap by default, `new PriorityQueue<>(Collections.reverseOrder())` for a max-heap. The defaults are opposite in the two languages, which is worth checking rather than recalling.

## Pitfalls

- **Assuming the heap is sorted.** Only the top is guaranteed. Iterating the backing array gives arbitrary order, and `heap[1]` is not the second smallest — it is one of the two candidates for it.
- **Updating a priority in place.** Mutating an element already inside the heap silently breaks the invariant, since nothing re-sifts it. Standard libraries offer no `decrease-key`. The usual workaround is **lazy deletion**: push a new entry with the updated priority and leave the stale one behind, then discard entries on pop that are recognisably out of date. Dijkstra is normally written this way, which is why the heap can hold more than one entry per node and why popped nodes get a `visited` check.
- **Choosing the wrong heap type for top-K.** Covered above; the symptom is an algorithm that works but is O(N log N) with O(N) memory instead of O(N log K) with O(K).
- **Reaching for a heap when sorting is simpler.** If K is close to N, or the input is needed in full sorted order anyway, just sort — O(N log N) with a far smaller constant. A heap wins when K ≪ N, when the input is a stream of unknown length, or when insertions interleave with removals.
- **Forgetting quickselect exists.** For an offline "Kth largest" on an array in memory, quickselect averages O(N) and beats O(N log K). The heap is the better answer when the data arrives incrementally or must not all be held at once; quickselect needs the whole array and permutes it.
