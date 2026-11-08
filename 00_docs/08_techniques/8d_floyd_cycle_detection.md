# Floyd's Cycle Detection (Tortoise and Hare)

## What it solves

Take any process that moves from one state to the next by a fixed rule, `x → f(x)`, over a finite set of states. Following a linked list's `next` pointers is one. Jumping `i → nums[i]` in an array is another. So is replacing a number with the sum of the squares of its digits.

Because the set of states is finite and every state has exactly one successor, the walk either reaches a dead end (a `null`, a terminal value), or it repeats a state. Once it repeats, it loops forever. The path has the shape of the Greek letter **rho (ρ)**: a straight **tail** followed by a **cycle**.

```
x0 → x1 → x2 → x3 → x4 → x5
                ↑         ↓
                x8 ← x7 ← x6

tail:  x0 x1 x2              length a = 3
cycle: x3 x4 x5 x6 x7 x8     length c = 6,  entrance x3
```

Floyd's algorithm answers three questions about that shape in **O(a + c) time and O(1) memory**, without storing visited states:

1. Is there a cycle at all?
2. Where does it start (the entrance)?
3. How long is it?

A hash set of visited states answers all three too, in the same time, but with O(a + c) memory. Floyd is the answer when the problem says "O(1) extra space", or when states are too large to store.

## Phase 1: detect the cycle

Move two pointers from the start: `slow` one step at a time, `fast` two steps at a time.

- If there is no cycle, `fast` reaches the dead end first, and you stop.
- If there is a cycle, both pointers eventually enter it, and `fast` catches `slow`.

Once both are in the cycle, measure the gap from `fast` forward to `slow`. Each step, `fast` gains 2 and `slow` gains 1, so the gap shrinks by exactly 1. A gap that shrinks by 1 cannot jump over 0, so they meet within `c` steps of `slow` entering the cycle. They meet before `slow` completes a lap.

With a speed difference of 2 instead of 1, the gap could skip from 1 to -1 and the pointers could pass each other without ever landing on the same node. Speeds 1 and 2 are the standard choice for this reason.

**Linked List Cycle (141)**, with `null` as the dead end:

```cpp
bool hasCycle(ListNode *head) {
  ListNode *slow = head, *fast = head;
  while (fast && fast->next) {         // fast checks both steps
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return true;
  }
  return false;                        // fast hit null: no cycle
}
```

Check `fast` *and* `fast->next` before stepping. `fast->next->next` on a list of odd length dereferences `null`.

## Phase 2: find the entrance

The meeting point is somewhere inside the cycle, usually not at the entrance. To find the entrance, put one pointer back at the start and move both pointers **one step at a time**. They meet exactly at the entrance.

Why: let `a` be the tail length, `c` the cycle length, and `b` the distance from the entrance forward to the meeting point. When they meet, `slow` has taken `a + b` steps. `fast` has taken twice as many, which is the same `a + b` plus `k ≥ 1` full laps:

```
2(a + b) = a + b + k·c
   a + b = k·c
       a = (k - 1)·c + (c - b)
```

Walking `c - b` steps from the meeting point reaches the entrance, and every further `c` steps is a full lap back to it. So `a` steps from the meeting point ends at the entrance, and `a` steps from the start ends there too. Nobody knows `a`, but the two pointers do not need it. Moving at the same speed, they arrive together.

Three details make the argument work:

- **`slow` has not finished a lap when they meet.** The gap closes within `c` steps of `slow` entering the cycle, so `slow`'s distance is exactly `a + b`, with no extra laps on its side.
- **`k` can be greater than 1.** If the tail is long and the cycle short, `fast` circles several times while `slow` is still in the tail. The pointer starting at the meeting point then goes around `k - 1` extra times in phase 2 before the other one arrives. The proof only uses `a ≡ c - b (mod c)`, which holds for any `k`. The trace below has `k = 2`.
- **Nothing assumes `a < c`,** or any other relation between the tail and the cycle.

### A full trace

The step function `0→1, 1→3, 3→2, 2→4, 4→2`:

```
0 → 1 → 3 → 2 ⇄ 4

tail 0 1 3      a = 3
cycle 2 4       c = 2,  entrance 2
```

Phase 1, `slow` one step, `fast` two:

```
step    0  1  2  3  4
slow    0  1  3  2  4
fast    0  3  4  4  4      meet at 4 after 4 steps
```

The meeting point 4 is one step past the entrance, so `b = 1`. `slow` walked `4 = a + b`. `fast` walked `8 = a + b + 2c`, so `k = 2`, and `a = (k - 1)·c + (c - b) = 2 + 1 = 3`.

Phase 2, both one step:

```
step         0  1  2  3
from start   0  1  3  2
from meet    4  2  4  2      both on 2 after a = 3 steps
```

The pointer from the meeting point does `c - b = 1` step to reach the entrance, then one extra full lap (`k - 1 = 1`), and arrives with the other pointer.

**Linked List Cycle II (142)** returns the entrance node:

```cpp
ListNode *detectCycle(ListNode *head) {
  ListNode *slow = head, *fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {                // phase 1 done
      ListNode *p = head;
      while (p != slow) {              // phase 2: both at speed 1
        p = p->next;
        slow = slow->next;
      }
      return p;
    }
  }
  return nullptr;
}
```

## Phase 3 (optional): measure the cycle

From the meeting point, keep one pointer still and walk the other until it comes back, counting steps. The count is `c`. The tail length `a` is the number of steps phase 2 took.

## Complexity

Phase 1 takes at most `a + c` steps: `a` to bring `slow` into the cycle, then fewer than `c` to close the gap. Phase 2 takes `a` steps, and phase 3 takes `c`. Since `a + c` is at most the number of distinct states, the total is **O(number of states) time** and **O(1) space**, just a few pointers or integers. In 287, that is O(n) time with the array only ever read.

## The same shape outside linked lists

The algorithm only needs the step function `f`. It does not care what the states are.

**Find the Duplicate Number (287).** An array of `n + 1` values in `[1, n]` holds one repeated value. The array must stay read-only, and only O(1) extra space is allowed. That rules out a hash set (O(n) space), sorting (modifies the array), and marking visited values by negating them (also modifies it).

Every value is a valid index, so `f(i) = nums[i]` is a step function on indices `0..n`. Read each index as a node with one edge to `nums[i]`, and the array becomes an implicit linked list. Three facts follow from the value range:

1. **Every node has exactly one outgoing edge**, so a walk never stops. On `n + 1` nodes it must repeat, so there is always a cycle.
2. **No value is 0, so no edge points to index 0.** A node on a cycle needs an incoming edge from the cycle, so index 0 is never on the cycle. Starting there guarantees a non-empty tail.
3. **The cycle entrance is the duplicate.** The entrance is the one node on the walk with two incoming edges: one from the last tail node and one from the last cycle node. Two different indices `i` and `j` pointing at the same node means `nums[i] == nums[j]`, which is exactly the repeated value.

Nodes not reachable from index 0 do not matter. The walk from 0 still runs into the duplicate.

The trace above is `nums = [1, 3, 4, 2, 2]`: indices 3 and 4 both hold 2, and the entrance is 2. Phase 1 and phase 2 on `nums` return the duplicate directly.

```cpp
int slow = 0, fast = 0;
do {                                   // both start at 0: do/while
  slow = nums[slow];
  fast = nums[nums[fast]];
} while (slow != fast);

slow = 0;
while (slow != fast) {
  slow = nums[slow];
  fast = nums[fast];
}
return slow;                           // entrance index = duplicate value
```

The answer is the entrance *index*, which equals the duplicate *value*, because the duplicate value is the index that both copies point to.

**Happy Number (202).** Replace `n` with the sum of the squares of its digits and repeat. The number is happy if this reaches 1. Any number with 4 or more digits shrinks under this step, so every walk ends up below 1000 and must cycle. 1 is a fixed point, `f(1) = 1`, so a happy number's walk cycles at 1. Run phase 1 and check whether the meeting point is 1:

```cpp
int next(int n) {
  int s = 0;
  for (; n; n /= 10) s += (n % 10) * (n % 10);
  return s;
}

bool isHappy(int n) {
  int slow = n, fast = next(n);
  while (fast != 1 && slow != fast) {
    slow = next(slow);
    fast = next(next(fast));
  }
  return fast == 1;
}
```

There is no dead end here. Every walk cycles, and the question is only *which* cycle.

**Beyond interview problems.** Pollard's rho factoring algorithm and period detection in pseudo-random number generators use the same idea. Both iterate a function over a huge finite set, where storing every visited value is not an option.

## Fast and slow without a cycle: the middle of a list

The same two speeds also find the **middle of a list** (876). When `fast` reaches the end, `slow` has gone half as far. Whether you get the first or second middle of an even-length list depends on the loop condition:

```
while (fast && fast->next)    →  second middle   [1 2 3 4] → 3
while (fast->next && fast->next->next)  →  first middle  [1 2 3 4] → 2
```

Palindrome Linked List and Reorder List both start by finding the middle this way.

## Brent's algorithm

Brent's variant uses one moving pointer and one stationary pointer. The stationary pointer teleports to the moving one at powers of two: after 1, 2, 4, 8, ... steps. A cycle is found when the moving pointer lands on the stationary one, and the step count since the last teleport is the cycle length `c`. It makes fewer calls to `f` than Floyd, which matters when `f` is expensive, as in Pollard's rho. For interview problems, Floyd is enough.

## How to spot it

- The problem asks to detect a cycle, find where it starts, or find a repeated element, **with O(1) extra space**.
- Each state has **exactly one next state**: a `next` pointer, `nums[i]` as an index, or a numeric transformation applied repeatedly.
- The values are **valid indices into the same array**, as in `[1, n]` with `n + 1` slots. That turns the array into a step function.
- The question is "does this repeated process terminate or loop forever?"

## When it's the wrong tool

- **States with several successors**, as in general graphs. Floyd needs exactly one next state. Directed cycle detection in graphs uses three-colour DFS or Kahn's algorithm ([`9b_topological_sort.md`](../09_graphs/9b_topological_sort.md)). Undirected cycle detection uses Union-Find or a DFS with a parent check.
- **Memory is not constrained.** A hash set of visited states is easier to write and gives the same O(n) time.
- **You need every repeated value**, not one cycle entrance. Each walk finds one entrance. Several duplicates need counting or marking.

## Pitfalls

- **`while` instead of `do/while` when both pointers start on the same state.** They compare equal before moving, and the loop exits immediately. Either use `do/while`, or start `fast` one step ahead and adjust the phase-2 start to match.
- **Mixing two start conventions.** If phase 1 starts `fast = f(start)` instead of `start`, phase 2 must also shift by one step, or it returns the node next to the entrance. Pick one convention and keep it.
- **Checking only `fast->next`.** `fast` itself may already be `null` on an even-length list. Check `fast && fast->next` in that order.
- **Moving `fast` two steps in phase 2.** Both pointers move one step in phase 2. With two steps, the distance argument no longer holds, and the pointers usually never meet at the entrance.
- **Returning `nums[p]` instead of `p` in 287.** The entrance is an index, and that index is the duplicate.
- **Comparing values instead of nodes** in linked lists. Two different nodes can hold the same `val`. Compare pointers.
