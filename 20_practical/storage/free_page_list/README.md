# Free Page List

A database file is split into fixed-size pages, numbered from 0. When a table shrinks, its pages are freed and later reused, so the file does not keep growing.

## Stages

1. **Allocate and free.** The file starts with `n` pages, all free, handed out in order 0, 1, 2, … `free(page)` returns a page, and `allocate()` returns the most recently freed page first. Both O(1).
2. **Validation.** Reject freeing a page outside the file, and freeing a page that is already free (a double free).
3. **Growth.** When no page is free, `allocate()` grows the file by one page and returns it.
4. **Statistics.** `freeCount()` and `pageCount()` in O(1).

## Design notes

The free pages form a linked list stored inside the free pages themselves: each free page holds the number of the next one, and only the head is kept outside. A free page's contents are unused anyway, so the list needs no extra space. Here that storage is simulated by an array indexed by page number. SQLite's freelist works on the same idea.

A linked list cannot tell whether a page is already in it without walking it, so a bitmap marks the free pages. Without the check, freeing a page twice puts it in the list twice, and two later allocations return the same page to two different owners.

## Changes from the original version

The original allocated a separate node object for each free page and accepted any `free` call, so a double free put a page in the list twice. It returned null when no page was free instead of growing the file.

## Files

`FreePageList.java`: the solution, with checks for each stage in `main`. Run with `java FreePageList.java` (Java 21+).
