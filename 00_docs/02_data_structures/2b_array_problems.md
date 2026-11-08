# Array and Hashing Problems

The problems in `01_arrays/` are short, but each one turns on a single idea: a hash set that answers "is this value present" in O(1), a key that makes equal things look equal, a length written in front of a string, or a formula that maps a cell to its group. This page goes through the ones that need more than a direct lookup. Hash maps and sets themselves are covered in [hashing](2a_hashing.md).

The examples follow the C++ solutions in `01_arrays/`. Every trace was produced by running the same steps on the input shown.

## Product of Array Except Self (238)

The task: return an array where `ans[i]` is the product of every element except `nums[i]`, in O(n) time and without division.

Dividing the total product by `nums[i]` fails when the array contains a 0, and the problem forbids division anyway. Instead, split the product at position `i` into two parts:

```
ans[i] = (product of everything left of i) × (product of everything right of i)
```

The solution computes both parts for every `i` in two passes:

- `prefixes[i]` is the product of `nums[0 .. i-1]`. `prefixes[0]` is 1, the product of nothing.
- `suffixes[i]` is the product of `nums[i+1 .. n-1]`. `suffixes[n-1]` is 1.

```cpp
prefixes[0] = 1;
for (int i = 1; i < n; i++)
    prefixes[i] = prefixes[i - 1] * nums[i - 1];
suffixes[n - 1] = 1;
for (int i = n - 2; i >= 0; i--)
    suffixes[i] = suffixes[i + 1] * nums[i + 1];
for (int i = 0; i < n; i++)
    ans[i] = prefixes[i] * suffixes[i];
```

For `nums = [1, 2, 3, 4]`:

```
i           0    1    2    3
nums        1    2    3    4
prefixes    1    1    2    6
suffixes   24   12    4    1
ans        24   12    8    6
```

`ans[2] = 8` is `(1 × 2) × 4`: everything left of 3 times everything right of it.

The solution uses two extra arrays of size `n`. They can be removed: store the prefix products directly in `ans`, then walk from the right with a single running suffix product and multiply it in. That leaves O(1) extra space besides the output.

Prefix products are the multiplicative version of prefix sums, covered in [prefix sums](2c_prefix_sums.md).

## Longest Consecutive Sequence (128)

The task: find the length of the longest run of consecutive integers in an unsorted array, in O(n). Sorting would give O(n log n).

The solution puts every value in a hash set. A run can then be measured by counting upwards from its first value: is `x + 1` present, then `x + 2`, and so on. The important part is **where** counting starts:

```cpp
unordered_set<int> set(nums.begin(), nums.end());
for (int n : set) {
    if (!set.contains(n - 1)) {          // n starts a run
        int count = 1;
        while (set.contains(n + count))
            count++;
        max = std::max(max, count);
    }
}
```

Counting starts only at a value `n` whose predecessor `n - 1` is **not** in the set, which makes `n` the first value of its run.

For `[100, 4, 200, 1, 3, 2]`:

```
value   n - 1 present?   action
 100        no           count from 100: run length 1
   4        yes (3)      skip: not the start of a run
 200        no           count from 200: run length 1
   1        no           count from 1: 2, 3, 4 present → run length 4
   3        yes (2)      skip
   2        yes (1)      skip
```

The answer is 4.

**Why this is O(n).** The `while` loop only runs from the start of a run, and walks that run once. Every value belongs to exactly one run, so across the whole loop each value is stepped over by the `while` loop at most once. In the trace the `while` loop advances 3 times in total, for the values 2, 3 and 4. Without the `n - 1` check, counting would start from every value, and a single run of length `n` would cost `n + (n-1) + … + 1`, which is O(n²).

The loop goes over the set rather than the input array. With repeated values, looping over the array could start counting the same run once per copy of its first value.

## Encode and Decode Strings (271)

The task: turn a list of strings into one string, and back. The strings may contain any character.

Joining with a separator such as `,` fails as soon as a string contains a `,`: the decoder cannot tell a separator from a character inside a string. Escaping the separator works but is fiddly.

The solution writes each string's **length** in front of it, followed by a delimiter:

```
["lint", "code", "love", "you"]   →   "4-lint4-code4-love3-you"
```

The decoder reads digits up to the next `-`, which gives the length `L`, then takes exactly the next `L` characters as the string, whatever they are:

```cpp
while (i < s.size()) {
    int delimPos = s.find('-', i);
    int len = stoi(s.substr(i, delimPos - i));
    res.push_back(s.substr(delimPos + 1, len));
    i = delimPos + 1 + len;
}
```

The first `-` after `i` always ends the length, because the length is written in digits and digits never contain `-`. A `-` inside a string is never searched for, because the decoder jumps over the whole string using its length. For `["a-b", "", "5-", "12-x"]` the encoding is `"3-a-b0-2-5-4-12-x"`, and decoding gives back the same four strings, including the empty one.

## Valid Sudoku (36)

The task: check whether the filled cells of a 9 × 9 board break a rule. No digit may repeat in a row, a column, or one of the nine 3 × 3 boxes.

The repo has four solutions. The first checks the rows, then the columns, then the boxes, in three separate passes. The others do it in one pass, which needs to know which box each cell belongs to.

### The box index

Number the boxes 0 to 8, left to right and top to bottom. Row `r` is in box row `r / 3`, and column `c` is in box column `c / 3` (integer division). The box number is:

```
box = (r / 3) * 3 + (c / 3)
```

For every cell:

```
          c: 0 1 2   3 4 5   6 7 8
r = 0..2     0 0 0   1 1 1   2 2 2
r = 3..5     3 3 3   4 4 4   5 5 5
r = 6..8     6 6 6   7 7 7   8 8 8
```

### One pass

The third solution keeps `seenRows[9][9]`, `seenCols[9][9]` and `seenBoxes[9][9]`, one "seen" flag per digit for each row, column and box. Each filled cell checks and sets three flags:

```cpp
int d = board[i][j] - '1';              // digit 1..9 → index 0..8
int box = (i / 3) * 3 + (j / 3);
if (seenRows[i][d] || seenCols[j][d] || seenBoxes[box][d]) return false;
seenRows[i][d] = seenCols[j][d] = seenBoxes[box][d] = true;
```

The fourth solution stores each group's nine flags as the bits of one integer, `seenRows[i] |= 1 << d` ([masking](../11_bit_manipulation/11d_masking.md#an-integer-as-a-set)).

The board is always 9 × 9, so every solution is O(81) = O(1). The difference between them is the number of passes and the memory layout.

## Group Anagrams (49): choosing the key

The task: group strings that are anagrams of each other.

All three solutions decide whether two strings are anagrams. They differ in how they do it:

- **Compare every pair.** For each string, check it against the first string of every existing group. With `n` strings of length `k`, this is O(n² · k).
- **Sorted key.** Sort each string's letters. Anagrams give the same sorted string, so it can be a hash map key: `"eat"`, `"tea"` and `"ate"` all become `"aet"`. O(n · k log k).
- **Count key.** Count each letter and write the 26 counts into a string, such as `"1#0#0#0#1#…"`. Anagrams have the same counts. O(n · k), plus 26 per string to build the key.

The last two follow one rule: compute a **canonical key**, a value that is equal for two items exactly when they belong to the same group. Then a hash map groups them in one pass. The `#` between counts is needed for the same reason as the length prefix in problem 271: without it, counts `1, 12` and `11, 2` would both become `"112"`.

## Top K Frequent Elements (347): four costs

The task: return the `k` most frequent values. Every solution first counts frequencies in a hash map, O(n). With `m` distinct values, they differ in how they pick the top `k`:

| Solution | Method | Time after counting |
|---|---|---|
| 1 | sort all `m` (value, count) pairs by count | O(m log m) |
| 2 | push all `m` into a max-heap one by one, then pop `k` | O(m log m + k log m) |
| 3 | min-heap kept at size `k`: push, and pop when larger than `k` | O(m log k) |
| 4 | bucket by count, read buckets from the highest count down | O(n) |

The bucket version works because a count is at most `n`, so an array of `n + 1` buckets indexed by count holds every value. For `[1, 1, 1, 2, 2, 3]`:

```
count:    0    1     2     3     4   5   6
bucket:   []  [3]   [2]   [1]   []  []  []
```

Reading from count 6 down, the first two values found are 1 and 2. Bucket sort is covered in [bucket sort](../05_sorting_and_searching/5b_bucket_sort.md), and heaps in [heaps](2g_heaps_and_priority_queues.md).
