# Complexity Analysis

## What big-O actually says

Big-O describes how the running time **grows** as the input grows. It is not a measurement, and it deliberately ignores two things:

- **Constant factors.** `3n` and `n/2` are both O(n).
- **Lower-order terms.** `n² + 500n + 9000` is O(n²), because for large `n` the `n²` term dwarfs the rest.

The reason for throwing that detail away is that it is machine-dependent and the growth rate is not. An O(n log n) algorithm beats an O(n²) one on large inputs regardless of language, hardware, or how tight the inner loop is.

The cost of the abstraction: on *small* inputs, constants decide everything. Insertion sort is O(n²) and beats merge sort below roughly 16 elements, which is why real library sorts switch to it (see [`5a_sorting.md`](../05_sorting_and_searching/5a_sorting.md)). Big-O answers "will this scale", not "which is faster here".

```
n=10      n=100       n=1,000      n=1,000,000
O(1)         1            1            1               1
O(log n)     3            7           10              20
O(n)        10          100        1,000       1,000,000
O(n log n)  33          664        9,966      19,931,569
O(n²)      100       10,000    1,000,000   10¹²  (too slow)
O(2ⁿ)    1,024      10³⁰ (hopeless)
```

## Reading complexity off code

Three mechanical rules cover nearly everything.

**Sequential blocks add.** Two loops one after the other, `O(n) + O(n)`, is `O(n)` — addition keeps only the larger term.

**Nested loops multiply.**

```python
for i in range(n):          # n times
    for j in range(n):      # × n times
        do_something()      # × O(1)
# O(n²)
```

**A loop that divides is logarithmic.** If the remaining work shrinks by a constant *factor* each step rather than by a constant *amount*, the count of steps is `log n`.

```python
while n > 1:
    n //= 2       # halving → log₂ n iterations
```

Halving `n` until you reach 1 takes `log₂ n` steps, by the definition of a logarithm. This is why binary search, heap operations, and balanced-tree operations are all O(log n) — they all discard a constant fraction per step.

The base of the logarithm never appears in big-O, because changing base only multiplies by a constant: `log₂ n = log₁₀ n / log₁₀ 2`.

### The trap: the loop bound is not the iteration count

```python
for i in range(n):
    j = i
    while j < n:
        j *= 2         # inner loop runs log(n/i) times, not n
```

Count what the loop body actually does, not how the loop looks. Two specific cases matter:

**Amortised inner loops.** A nested `while` is not automatically O(n²).

```python
for right in range(n):
    while stack and stack[-1] < nums[right]:
        stack.pop()
    stack.append(nums[right])
```

This looks quadratic and is **O(n)**. Each element is pushed exactly once and popped at most once, so there are at most `n` pops across the entire run. Count the total work, not the nesting depth. The same argument makes the monotonic stack ([`2d_stacks.md`](../02_data_structures/2d_stacks.md)), the monotonic deque ([`2f_queues_and_deques.md`](../02_data_structures/2f_queues_and_deques.md)), and the sliding window linear.

**Work proportional to something other than `n`.** String operations are the usual surprise. `s[i:j]` costs O(j − i), not O(1), so slicing inside a loop adds a factor. Comparing two strings costs up to their length, so sorting `n` strings of length `L` is O(L · n log n).

## Recursion

For recursion, count the total number of calls and multiply by the work per call.

```python
def f(n):
    if n <= 1: return 1
    return f(n - 1) + 1        # n calls, O(1) each → O(n)

def g(n):
    if n <= 1: return 1
    return g(n // 2) + 1       # log n calls → O(log n)

def h(n):
    if n <= 1: return 1
    return h(n - 1) + h(n - 1) # 2 calls per level, n levels → O(2ⁿ)
```

Drawing the call tree makes the count visible: **branching factor ^ depth** is the number of leaves.

```
h(3)                          branching 2, depth 3
├── h(2)                      leaves = 2³ = 8
│   ├── h(1)
│   └── h(1)
└── h(2)
    ├── h(1)
    └── h(1)
```

Two shortcuts that cover most of what you will meet:

**Divide and conquer that splits in half and does linear work per level** is O(n log n). There are `log n` levels and each level's pieces sum to `n` items of work.

```
merge sort:   n
            n/2  n/2                 log n levels
          n/4 n/4 n/4 n/4            n work per level
                                     → O(n log n)
```

**Halving with constant work per level** is O(log n); **halving but following only one branch** is what makes binary search logarithmic while merge sort is linearithmic. The difference is whether you recurse into one half or both.

**Tree and graph recursion** is O(V + E) — each node visited once, each edge examined once. For a binary tree that is O(n). See [`11a_graphs_bfs_dfs.md`](../11_graphs/11a_graphs_bfs_dfs.md).

**Memoized recursion** is the cleanest case: `number of distinct states × work per state`, because each state is computed once and thereafter read from the cache (see [`12a_dynamic_programming.md`](../12_dynamic_programming/12a_dynamic_programming.md)).

## Worst, average, and amortised

These three get conflated, and the distinction is the difference between reciting a complexity and understanding it.

**Worst case.** The slowest possible input. This is what "O(...)" means unless stated otherwise, and it is what you should quote by default.

**Average case.** Over a random input, or with random choices inside the algorithm. Quicksort is O(n log n) average and O(n²) worst; hash map lookup is O(1) average and O(n) worst when everything collides. Quoting the average as if it were the worst is the most common analysis error in interviews.

**Amortised.** The average cost *per operation across a sequence*, where one occasional expensive operation is paid for by many cheap ones. This is a guarantee, not a probability — unlike the average case, it does not depend on the input being nice.

The canonical example is a dynamic array. Appending is O(1), except when the array is full and must be reallocated at double size and copied, which is O(n).

```
push:  1  2  3  4  5  6  7  8  9 ...
copy:  ·  2  ·  4  ·  ·  ·  8  ·        copies at 2, 4, 8, 16, ...

total copying across n pushes:  1 + 2 + 4 + ... + n  <  2n
cost per push:                  2n / n = O(1) amortised
```

The expensive operations get rarer at exactly the rate they get more expensive, so the sum stays linear. The same argument justifies O(1) amortised hash map insertion ([`2a_hashing.md`](../02_data_structures/2a_hashing.md)) and the O(n) monotonic stack above.

## Space complexity

Count the **extra** memory your algorithm allocates, not the input, unless the problem says otherwise.

What counts, and is often forgotten:

- **The recursion stack.** A recursive tree traversal uses O(h) space — O(log n) balanced, O(n) on a degenerate tree. An algorithm is not O(1) space just because it declares no arrays.
- **The output**, sometimes. Conventionally excluded when the output is the answer itself, but a backtracking solution producing 2ⁿ subsets genuinely uses exponential memory and you should say so.
- **Slices and copies.** `path[:]` in a loop, or building a new string per iteration, is real allocation.

```python
def f(nums):
    total = 0                    # O(1)
    for x in nums: total += x
    return total

def g(nums):
    return [x * 2 for x in nums] # O(n)
```

Time and space trade against each other constantly. A hash map turns an O(n²) scan into O(n) time at the cost of O(n) space — the single most common trade in this problem set.

## The complexities you will actually meet

| Class | Name | Typical source |
|---|---|---|
| O(1) | constant | arithmetic, array index, hash lookup, heap peek |
| O(log n) | logarithmic | binary search, heap push/pop, balanced tree op |
| O(n) | linear | single pass, two pointers, sliding window, DFS/BFS |
| O(n log n) | linearithmic | sorting, heap over all elements, divide and conquer |
| O(n²) | quadratic | nested loops, 2D DP over two indices |
| O(n³) | cubic | interval DP, Floyd-Warshall |
| O(2ⁿ) | exponential | subsets, unmemoized branching recursion |
| O(n!) | factorial | permutations |

Some that look unusual and are not:

- **O(n + m)** — two different inputs. Do not collapse them into O(n); the distinction matters when one is far larger.
- **O(n log k)** — a bounded heap of size k over n elements. Strictly better than O(n log n) when k ≪ n.
- **O(V + E)** — graph traversal. Not O(V · E).
- **O(n · W)** — knapsack. **Pseudo-polynomial**: polynomial in the *value* of W, not in its number of bits, so a capacity of 10⁹ is intractable regardless of how few items there are.
- **O(4^L · R · C)** — grid backtracking with path length L.
- **O(α(n))** — union-find with path compression. The inverse Ackermann function is below 5 for any conceivable input, so treat it as constant.

## Stating it correctly

A few conventions that are worth following, because getting them wrong signals imprecision:

- **Drop constants and lower terms.** Write O(n), never O(2n) or O(n + 5).
- **Keep distinct variables.** O(n · m) is not O(n²) unless you know `n = m`.
- **Say which case you mean.** "O(n log n) average, O(n²) worst for quicksort."
- **Quote time and space separately.** Both are asked for.
- **O is an upper bound.** Θ is a tight bound. Saying an algorithm is "O(n²)" when it is actually linear is technically true and practically misleading; say what it is.

## Common mistakes

- **Reading a nested loop as quadratic without counting total work.** Monotonic stacks and sliding windows are linear.
- **Forgetting the recursion stack** when claiming O(1) space.
- **Forgetting the cost of an operation inside the loop** — slicing, string concatenation, `list.pop(0)`, `in` on a list (O(n), unlike `in` on a set).
- **Quoting the average as the worst** for quicksort and hash maps.
- **Ignoring the cost of building the input structure.** Sorting first means the whole solution is at least O(n log n).
- **Treating `n log n` as close to `n²`.** At n = 10⁶ the gap is a factor of 50,000 — the difference between instant and a week.
