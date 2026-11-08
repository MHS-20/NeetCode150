# Greedy Problems, with Proofs and Traces

Each problem below has a one-pass greedy solution, a short argument for why the greedy choice is safe, and a trace on a small input. The two proof styles, the exchange argument and "greedy stays ahead", are explained in [greedy proofs](8b_greedy_proofs.md).

The examples follow the C++ solutions in `15_greedy/`. Every trace was produced by running the same steps on the input shown.

## Maximum Subarray (53): Kadane's algorithm

The task: find the largest sum of a non-empty contiguous subarray.

The solution keeps `sum`, the sum of the best subarray that ends at the current index, and `mx`, the best sum seen so far. After adding the current element, if `sum` is negative it is reset to 0:

```cpp
int sum = 0, mx = INT_MIN;
for (int x : nums) {
    sum += x;
    mx = max(sum, mx);
    if (sum < 0)
        sum = 0;          // a negative prefix only lowers what follows
}
```

**Why dropping a negative prefix is safe.** Any subarray that starts after the current index and extends a prefix with a negative sum has a larger sum without that prefix. So no optimal subarray begins with a prefix whose sum is negative, and dropping it loses nothing.

`mx` is updated **before** the reset. If every element is negative, the answer is the largest single element, and that element is recorded in `mx` before `sum` goes back to 0. `mx` starts at `INT_MIN` for the same reason.

For `[-2, 1, -3, 4, -1, 2, 1, -5, 4]`:

```
x     sum after adding   reset?   sum after   mx
-2         -2             yes         0       -2
 1          1                         1        1
-3         -2             yes         0        1
 4          4                         4        4
-1          3                         3        4
 2          5                         5        5
 1          6                         6        6
-5          1                         1        6
 4          5                         5        6
```

The answer is 6, from `[4, -1, 2, 1]`.

The repo's version resets with `sum = nums[i] < 0 ? 0 : nums[i]`. The `nums[i]` branch never runs. `sum` is never negative before `nums[i]` is added, because of the previous reset, so if `sum` is negative afterwards, `nums[i]` itself must be negative and the reset sets 0. Over 20 000 random arrays the branch was taken 0 times, and the results matched a brute-force check every time. `sum = 0` alone behaves the same.

Kadane's algorithm can also be read as a DP whose table has collapsed to one variable: `best ending at i = max(nums[i], best ending at i-1 + nums[i])`.

## Jump Game (55)

The task: `nums[i]` is the longest jump from index `i`. Decide whether the last index can be reached from index 0.

The solution keeps `mx`, the furthest index reachable so far. Its proof is the stays-ahead example in [greedy proofs](8b_greedy_proofs.md#example-jump-game-55).

```cpp
int mx = 0;
for (int i = 0; i < nums.size(); i++) {
    if (i > mx) return false;              // i cannot be reached
    mx = max(mx, i + nums[i]);
    if (mx >= (int)nums.size() - 1) return true;
}
```

```
[2, 3, 1, 1, 4]                     [3, 2, 1, 0, 4]
i   nums[i]   mx                    i   nums[i]   mx
0      2      2                     0      3      3
1      3      4  → reaches the end  1      2      3
                                    2      1      3
                                    3      0      3
                                    4: 4 > 3, cannot be reached → false
```

In the second array every jump from indices 0 to 3 lands at index 3 or earlier, and index 3 has a jump of 0.

## Jump Game II (45)

The task: the last index can always be reached. Find the smallest number of jumps.

Think of the indices in groups. Group 0 is index 0. Group 1 is every index reachable with one jump, group 2 every index reachable with two, and so on. The answer is the number of the group that contains the last index. This is a BFS over the indices, where each group is one level. The groups are contiguous ranges, so the BFS needs no queue:

- `end` is the last index of the current group.
- `far` is the furthest index reachable from any index seen so far. It is the end of the next group.
- When `i` reaches `end`, the current group is finished. One more jump is counted, and `end` moves to `far`.

```cpp
int end = 0, far = 0, count = 0;
for (int i = 0; i < nums.size() - 1; i++) {
    far = max(far, i + nums[i]);
    if (i == end) {
        count++;
        end = far;
    }
}
```

For `[2, 3, 1, 1, 4]`:

```
i   far   i == end?   jumps   end
0    2      yes         1      2      group 1 is indices 1..2
1    4                  1      2
2    4      yes         2      4      group 2 is indices 3..4
3    4                  2      4
```

The answer is 2: index 0 → 1 → 4. The loop stops before the last index. If it ran there, `i == end` could count a jump out of the last index, which is never needed.

## Gas Station (134)

The task: stations on a circle. At station `i` the car gets `gas[i]`, and driving to the next station costs `cost[i]`. Find the station from which the car can go all the way round, or -1. The answer is unique if it exists.

Two facts make one pass enough.

**If the total gas is less than the total cost, no start works.** The car would need more fuel than the whole circle provides. Otherwise a start exists.

**If the tank goes negative on the way from `s` to station `i`, no station between `s` and `i` works as a start.** Take any station `k` between them. The car started at `s` reached `k` with a tank of at least 0, since the tank had not yet gone negative. Starting at `k` means arriving there with exactly 0, which is no better. The car started at `s` still ran out by `i`, so a car started at `k` also runs out by `i`. The next possible start is `i + 1`.

```cpp
int total = 0, cur = 0, start = 0;
for (int i = 0; i < gas.size(); i++) {
    int diff = gas[i] - cost[i];
    total += diff;
    cur += diff;
    if (cur < 0) {           // no start up to i works
        start = i + 1;
        cur = 0;
    }
}
return total < 0 ? -1 : start;
```

For `gas = [1, 2, 3, 4, 5]`, `cost = [3, 4, 5, 1, 2]`:

```
i   gas - cost   tank     start   total
0       -2       -2 → 0     1      -2
1       -2       -2 → 0     2      -4
2       -2       -2 → 0     3      -6
3        3        3         3      -3
4        3        6         3       0
```

The total is 0, not negative, so the answer is station 3.

The repo's first solution checks the totals first, then simulates the drive around the circle, moving the start forward whenever the tank goes negative, until the car arrives back at the start.

## Hand of Straights (846)

The task: decide whether the cards can be split into groups of `groupSize` consecutive values.

**The forced choice.** The smallest remaining card has to be the **first** card of its group. A group containing it cannot start lower, because no card is lower. So the group is fixed: the smallest card and the next `groupSize - 1` values. If any of them is missing, no split exists.

This is a safe greedy choice in the strongest sense: every valid split makes the same choice, so there is nothing to exchange.

```cpp
map<int, int> count;                     // value -> copies left, sorted by value
for (int c : hand) count[c]++;
while (!count.empty()) {
    int start = count.begin()->first;    // smallest remaining card
    for (int v = start; v < start + groupSize; v++) {
        auto it = count.find(v);
        if (it == count.end()) return false;
        if (--it->second == 0) count.erase(it);
    }
}
return true;
```

For `hand = [1, 2, 3, 6, 2, 3, 4, 7, 8]`, `groupSize = 3`:

```
smallest   group      cards left
   1       1 2 3      2 3 4 6 7 8
   2       2 3 4      6 7 8
   6       6 7 8      (none)       → true
```

A sorted map gives the smallest card in O(log n) and each removal in O(log n), so the whole check is O(n log n).

## Merge Triplets to Form Target Triplet (1899)

The task: merging two triplets takes the maximum in each position. Decide whether some set of triplets merges into `target`.

A triplet with **any** value larger than the target's value in that position can never be used: merging only raises values, so the larger value would stay. Every other triplet is safe to merge, because none of its values exceeds the target. Merging all the safe triplets gives the largest result possible without going over. The target is reachable when that result equals it, which means each of the three target values appears in some safe triplet.

```cpp
bool found[3] = {false, false, false};
for (auto &t : triplets) {
    if (t[0] > target[0] || t[1] > target[1] || t[2] > target[2])
        continue;                          // would overshoot
    for (int i = 0; i < 3; i++)
        if (t[i] == target[i]) found[i] = true;
}
return found[0] && found[1] && found[2];
```

For `triplets = [[2, 5, 3], [1, 8, 4], [1, 7, 5]]` and `target = [2, 7, 5]`: `[1, 8, 4]` is skipped because 8 > 7. `[2, 5, 3]` supplies the 2, and `[1, 7, 5]` supplies the 7 and the 5. The answer is true.

## Partition Labels (763)

The task: split a string into as many parts as possible so that each letter appears in at most one part. Return the part lengths.

A part that contains a letter must reach the letter's **last** occurrence. So the current part has to extend at least to the last occurrence of every letter in it so far. The solution records each letter's last index, then scans, pushing `end` out to the last occurrence of each letter it meets. When `i` reaches `end`, every letter in the part is finished, and the part can end there:

```cpp
int last[26];
for (int i = 0; i < s.size(); i++) last[s[i] - 'a'] = i;
int start = 0, end = 0;
for (int i = 0; i < s.size(); i++) {
    end = max(end, last[s[i] - 'a']);
    if (i == end) {
        result.push_back(end - start + 1);
        start = i + 1;
    }
}
```

**Why cutting at the first possible point is safe.** The first cut is placed at the earliest index where a cut is allowed. Any valid split has its first cut at that index or later. Moving that cut earlier, to greedy's cut, keeps the split valid and does not reduce the number of parts. That is the exchange argument, applied to each cut in turn.

For `"ababcbacadefegdehijhklij"`:

```
part        letters      ends at index   length
ababcbaca   a b c              8            9
defegde     d e f g           15            7
hijhklij    h i j k l         23            8
```

The answer is `[9, 7, 8]`.

## Valid Parenthesis String (678)

The task: a string of `(`, `)` and `*`, where each `*` can be `(`, `)` or nothing. Decide whether some choice for the stars makes the parentheses balanced.

Trying every choice costs O(3^k) for `k` stars. The counter solution keeps a **range** instead: the smallest and largest number of open `(` possible after each character, over all choices of the stars so far.

- `(` raises both `lo` and `hi` by 1.
- `)` lowers both by 1.
- `*` lowers `lo` by 1 (read as `)`) and raises `hi` by 1 (read as `(`).

Two checks after each character:

- **`hi < 0`:** even with every star read as `(`, there are more `)` than `(`. No choice works, so the answer is false.
- **`lo < 0`:** some choices closed more than was open. Those choices are invalid, so `lo` is clamped to 0, which drops them.

At the end the string is valid if `lo == 0`: some choice leaves no `(` unclosed.

```cpp
int lo = 0, hi = 0;
for (char c : s) {
    if (c == '(')      { lo++; hi++; }
    else if (c == ')') { lo--; hi--; }
    else               { lo--; hi++; }
    if (hi < 0) return false;
    lo = max(lo, 0);
}
return lo == 0;
```

Traces, showing `(lo, hi)` after each character:

```
"(*))"    (  → (1,1)   *  → (0,2)   )  → (0,1)   )  → (0,0)       lo = 0: true
")*("     )  → hi = -1                                            false
"(((**"   (  → (1,1)   (  → (2,2)   (  → (3,3)   *  → (2,4)   *  → (1,5)
                                                                  lo = 1: false
```

In the last string, three `(` and only two stars leave at least one `(` open, whatever the stars are.

The repo's first solution uses two stacks of indices, one for unmatched `(` and one for `*`. Each `)` closes a `(` if there is one, and otherwise uses a star. At the end, each leftover `(` must be closed by a star that comes **after** it. That is O(n) time and O(n) space, where the counters use O(1).
