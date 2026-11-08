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

**Monotonic stack.** The stack holds the elements still waiting for their nearest greater (or smaller) element, sorted so that each new element pops and answers every waiting element it beats. One pass answers the question for every element in O(n). Daily Temperatures, Largest Rectangle in Histogram, Car Fleet and Trapping Rain Water use it. Traces and the O(n) argument are in [monotonic stack](2d_monotonic_stack.md).

## Pitfalls

- Popping or peeking an empty stack. Guard with `if st` — in Python `st[-1]` raises `IndexError`, and in C++ `top()` on an empty stack is undefined behaviour that will not announce itself.
- Forgetting the final emptiness check in matching problems. `"((("` pushes cleanly and never fails a comparison; the leftovers are the error.
