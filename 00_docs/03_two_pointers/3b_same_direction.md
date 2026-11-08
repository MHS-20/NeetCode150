# Two Pointers Moving in the Same Direction

In these problems both pointers start at the same end and move forward, at different speeds. The usual reason is to rewrite an array in place: one pointer reads every element, and the other marks where the next kept element should be written. Without the second pointer, removing an element from the middle of an array shifts every later element, which costs O(n) per removal and O(n²) overall.

None of the problems on this page are in `02_two_pointers/` yet. They are from the NeetCode 250 list, and each trace was produced by running the loop shown.

## Read and write pointers

`read` visits every element once. `write` is the length of the output built so far, so the kept elements are always `a[0 .. write-1]`. When `read` finds an element to keep, it copies it to `a[write]` and `write` moves forward.

```
a[0 .. write-1]      kept elements, final order
a[write .. read-1]   elements already read and either copied or dropped
a[read ..]           not read yet
```

`write` never passes `read`, so the copy never overwrites an element that has not been read yet.

### Remove Duplicates from Sorted Array (26)

The task is to keep the first copy of each value, in place, and return how many values are kept. The array is sorted, so all copies of a value are next to each other. An element is new if it differs from the last kept element, `a[write - 1]`:

```python
write = 1
for read in range(1, len(a)):
    if a[read] != a[write - 1]:
        a[write] = a[read]
        write += 1
return write
```

For `a = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]`, the loop returns 5 and the array starts with `[0, 1, 2, 3, 4]`. The elements after position 4 are left over from the input and do not matter.

### Move Zeroes (283)

The task is to move every 0 to the end while keeping the order of the other elements. Swapping instead of copying puts the zeros in the tail as a side effect:

```python
write = 0
for read in range(len(a)):
    if a[read] != 0:
        a[write], a[read] = a[read], a[write]
        write += 1
```

For `a = [0, 1, 0, 3, 12]`:

```
read  a[read]   array after step       write
 0       0      [0, 1, 0, 3, 12]         0      zero: skip
 1       1      [1, 0, 0, 3, 12]         1      swap a[0] and a[1]
 2       0      [1, 0, 0, 3, 12]         1      zero: skip
 3       3      [1, 3, 0, 0, 12]         2      swap a[1] and a[3]
 4      12      [1, 3, 12, 0, 0]         3      swap a[2] and a[4]
```

Everything between `write` and `read` is always zero, so each swap moves a zero from position `write` to position `read`.

## Merging from the back

### Merge Sorted Array (88)

`nums1` has `m` sorted values followed by `n` empty slots, and `nums2` has `n` sorted values. The task is to merge `nums2` into `nums1` in place.

Merging from the front would overwrite values of `nums1` that have not been placed yet. Merging from the back avoids that. The largest remaining value goes into the last free slot:

```python
i, j, k = m - 1, n - 1, m + n - 1
while j >= 0:
    if i >= 0 and nums1[i] > nums2[j]:
        nums1[k] = nums1[i]; i -= 1
    else:
        nums1[k] = nums2[j]; j -= 1
    k -= 1
```

For `nums1 = [1, 2, 3, 0, 0, 0]` and `nums2 = [2, 5, 6]`:

```
compare            write at k   nums1 after
3 vs 6 → 6             5        [1, 2, 3, 0, 0, 6]
3 vs 5 → 5             4        [1, 2, 3, 0, 5, 6]
3 vs 2 → 3             3        [1, 2, 3, 3, 5, 6]
2 vs 2 → 2 (nums2)     2        [1, 2, 2, 3, 5, 6]
```

`k` stays ahead of `i`: the slots from `k` to the end are always written before `i` reaches them, because `k - i` equals the number of values left in `nums2`. The loop stops when `nums2` is empty. Any values left in `nums1` are already in place.

### Squares of a Sorted Array (977)

The input is sorted but can contain negative numbers, so the squares are not sorted: `[-4, -1, 0, 3, 10]` squares to `[16, 1, 0, 9, 100]`. The largest square is always at one of the two ends. So this problem uses pointers from opposite ends ([opposite ends](3a_opposite_ends.md)), but writes the output from the back like the merge:

```
l   r   compare |a[l]| vs |a[r]|   output
0   4      4 vs 10 → 100            [_, _, _, _, 100]
0   3      4 vs 3  → 16             [_, _, _, 16, 100]
1   3      1 vs 3  → 9              [_, _, 9, 16, 100]
1   2      1 vs 0  → 1              [_, 1, 9, 16, 100]
2   2      0 vs 0  → 0              [0, 1, 9, 16, 100]
```

The loop runs while `l <= r`, not `l < r`, because the last remaining element still has to be written.

## Fast and slow pointers

A slow pointer that moves one step and a fast one that moves two steps find the middle of a linked list, and detect a cycle in a list or in a number sequence such as Happy Number (202). Both cases are covered in [Floyd's cycle detection](../08_techniques/8d_floyd_cycle_detection.md).

## From same-direction pointers to a sliding window

In a read/write pass, the two pointers mark different arrays: `write` marks the output, `read` the input. In a sliding window, both pointers mark the same subarray. `left` is its first element and `right` its last, and both only move forward. The window is covered in [sliding window](../04_sliding_window/4a_fixed_size.md).
