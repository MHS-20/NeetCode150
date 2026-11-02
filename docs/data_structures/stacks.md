# Stacks

## The structure

LIFO — last in, first out. Everything happens at one end, called the top.

- `push(x)` — add on top
- `pop()` — remove and return the top
- `peek()` / `top()` — read the top without removing it

```
        push ↓  ↑ pop
             [ D ]  ← top
             [ C ]
             [ B ]
             [ A ]  ← bottom
```

A queue is the same restriction applied to two different ends (FIFO); a stack reuses one. The restriction is the point: with only one reachable end, every operation is a single array write.

## Complexity

| Operation | Cost |
|---|---|
| push | O(1) amortised |
| pop | O(1) |
| peek | O(1) |
| search | O(n) |
| space | O(n) |

"Amortised" covers the array doubling — when the backing array fills, it is reallocated at twice the size and everything is copied, which is O(n). That happens after 1, 2, 4, 8, … pushes, so the copies sum to less than 2n across n pushes and the per-push average stays O(1).

No sifting, no pointer chasing, no rebalancing. A stack is the cheapest non-trivial data structure there is.

## Implementation

A plain dynamic array is the right choice in every language. Append and remove-last are already the array's fast operations, and the memory is contiguous.

```python
st = []
st.append(x)      # push
st[-1]            # peek — check `if st` first
st.pop()          # pop
```

A linked list also works (push/pop at the head is O(1)) and gives worst-case O(1) rather than amortised, but costs a pointer per element and destroys cache locality. Use it only when a single O(n) resize spike is unacceptable — real-time code, not interview code.

In Java use `ArrayDeque`, not `Stack`; the latter is legacy and synchronised. In C++, `std::stack` is an adapter over `std::deque` by default.

## The call stack is the same structure

Function calls push a frame holding local variables and a return address; returning pops it. This is why recursion depth is bounded and why a runaway recursion overflows.

The consequence worth using: **any recursive algorithm can be rewritten iteratively with an explicit stack**, doing by hand what the runtime was doing for you. That is the fix when a tree or graph is deep enough to blow the call stack.

```python
def inorder(root):                  # iterative, explicit stack
    st, cur, out = [], root, []
    while cur or st:
        while cur:
            st.append(cur)          # descend, remembering the path back
            cur = cur.left
        cur = st.pop()
        out.append(cur.val)
        cur = cur.right
    return out
```

DFS is a stack; BFS is a queue. Swapping the container swaps the traversal order, and nothing else in the loop changes.

## The problem shapes

**Matching pairs.** Valid Parentheses. Push each opener; on a closer, pop and check it matches. The stack must be empty at the end. This generalises to any nesting — tags, brackets, scopes.

```
"( [ ] )"    push (    push [    top [ matches ]  pop    top ( matches )  pop    empty ✓
```

**Undo / backtracking.** Simplify Path, Remove K Digits, Backspace String Compare. The stack holds committed decisions, and new input can revoke the most recent one.

**Deferred evaluation.** Evaluate Reverse Polish Notation, Basic Calculator. Push operands; an operator pops the operands it needs and pushes the result. Nesting is handled by pushing the outer context before descending into a parenthesis.

**Monotonic stack.** The one worth practising. Keep the stack's values sorted (increasing or decreasing) by popping anything that would break the order before pushing. Each popped element has just met the first later element greater (or smaller) than itself.

```
Next Greater Element in [2, 1, 5, 3]      decreasing stack, holds indices

x=2:  stack empty        push 2        [2]
x=1:  1 < 2, no pop      push 1        [2,1]
x=5:  5 > 1 → pop 1, answer for 1 is 5
      5 > 2 → pop 2, answer for 2 is 5
                         push 5        [5]
x=3:  3 < 5, no pop      push 3        [5,3]

leftovers 5 and 3 have no next greater → -1
```

Every element is pushed once and popped once, so the whole scan is **O(n)** despite the nested `while`. This is the pattern behind Daily Temperatures, Largest Rectangle in Histogram, Trapping Rain Water, and Car Fleet. Store indices rather than values whenever the answer needs a distance or a width.

The monotonic *stack* answers "nearest greater/smaller element"; the monotonic *deque* answers "max/min over a sliding window". Same popping logic, different ends available.

## Pitfalls

- Popping or peeking an empty stack. Guard with `if st` — in Python `st[-1]` raises `IndexError`, and in C++ `top()` on an empty stack is undefined behaviour that will not announce itself.
- Forgetting the final emptiness check in matching problems. `"((("` pushes cleanly and never fails a comparison; the leftovers are the error.
- Storing values in a monotonic stack when the problem asks for a distance or a width — the index is unrecoverable afterwards.
- Reading the nested `while` in a monotonic stack as O(n²). Count total pops, not loop nesting: n elements, at most n pops.
