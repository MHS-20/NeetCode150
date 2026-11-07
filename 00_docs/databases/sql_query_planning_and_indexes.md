# SQL: Query Planning and Indexes

SQL is declarative — you state *what* you want, not how to get it. The database decides the how, and everything below is about that decision: how a query becomes an execution plan, and how indexes change which plans are cheap.

The connection to the rest of these notes is direct. A database is the same set of data structures applied under one extra constraint: **data lives on disk, and a disk read costs roughly 100,000× a memory access.** Every design choice here follows from minimising reads rather than minimising comparisons.

## From SQL text to an execution plan

### 1. Parsing

The query text is parsed into an **AST**, then checked: do the tables exist, do the columns exist, are the data types compatible, does the user have permission. Syntax errors and unknown-column errors surface here, before any planning happens.

### 2. Logical query tree

The AST becomes a tree of relational operations — selection (`WHERE`), projection (`SELECT` columns), join, aggregation, sort. This describes **what** operations to perform, not **how** to execute them. A join at this stage is just "join"; nothing yet says nested-loop or hash.

### 3. Logical optimization

The tree is rewritten using algebraic rules that provably preserve the result:

- **Push filters down** — move `WHERE` conditions as close to the base tables as possible, so rows are discarded before they reach a join instead of after. Filtering a million rows down to a hundred before joining, rather than joining a million and filtering afterwards, is usually the single largest saving available.
- **Push projections down** — drop unneeded columns early, so less data moves between operators.
- **Reorder joins** — join order does not change the result but changes the cost enormously; joining the two smallest tables first keeps intermediate results small.
- **Flatten subqueries** into joins, eliminate redundant conditions, simplify constant expressions.

### 4. Cost-based optimization (CBO)

The optimizer generates multiple candidate **physical** plans — different concrete implementations of the same logical plan — and estimates the cost of each from statistics it keeps about the data: table sizes, available indexes, the number of distinct values in a column, value distribution histograms.

```sql
SELECT name
FROM employees
WHERE department = 'HR'
ORDER BY hire_date DESC;
```

```
Sort (hire_date DESC)
└── Index Scan (on employees(department))
     Filter: department = 'HR'
     Output: name, hire_date
```

For that query the optimizer is choosing between at least three plans:

- **Full table scan**, filter, then sort. Good if most employees are in HR — an index would add random reads for no benefit.
- **Index scan on `department`**, then sort. Good if HR is a small fraction of the table.
- **Index scan on `hire_date`** in reverse, filtering as it goes and stopping once enough rows are found. Good when there is a `LIMIT`.

The decision rests on **selectivity**: what fraction of rows survive the filter. Below roughly 5–10%, the index wins; above it, the scan does. This is why the same query can use an index on one table and ignore it on another, and why an index that helped last month can be abandoned after the data distribution shifts.

Cost estimates come from statistics that are sampled, not exact. Stale statistics are a common cause of a query that was fast yesterday and is slow today, and refreshing them (`ANALYZE`) is the first thing to try.

### 5. Execution

The physical plan runs, usually as a pipeline where each operator pulls rows from its children one at a time rather than materialising whole intermediate tables.

**`EXPLAIN`** prints the chosen plan; **`EXPLAIN ANALYZE`** runs it and prints the actual row counts and timings alongside the estimates. The gap between estimated and actual rows is the most useful diagnostic there is — a large divergence means the optimizer chose the plan on bad information.

## The B+ tree

Essentially every relational index is a B+ tree. Understanding its shape explains most index behaviour.

**Internal nodes store only keys and child pointers. All values (row references) live only in the leaves.**

```
                 [ 30 | 70 ]                     internal: keys + pointers only
                /     |     \
        [10|20]   [40|50|60]   [80|90]
           │          │           │
        leaves: keys + rows/pointers, linked left to right
        [10→][20→] ─ [40→][50→][60→] ─ [80→][90→]
```

Four consequences, each of them a design decision:

**Smaller internal nodes → fewer levels → fewer disk reads.** Because internal nodes hold no row data, more keys fit per page, so each node has a high fan-out and the tree stays shallow.

**Range queries are efficient.** All data sits in sorted leaf pages joined in a linked list, so `WHERE x BETWEEN 10 AND 60` descends once to find the start and then follows leaf-to-leaf pointers sequentially — no re-descending the tree per row, and sequential disk access rather than random.

**A node is sized to a page** (commonly 8 KB or 16 KB), which minimises I/O: one disk read brings an entire node into memory. Each node is serialized into a page on disk, and if that page is already in the buffer pool the read is skipped entirely.

**Leaves hold the serialized rows** in the primary index — see clustering below.

### Why the height is 3 or 4, not 30

A binary tree over a million rows is about 20 levels deep ([`binary_trees.md`](../data_structures/binary_trees.md)), and if each level were a separate disk read that would be 20 reads per lookup. A B+ tree node holding a few hundred keys has a fan-out of a few hundred, so the height is `log₍fanout₎ n` rather than `log₂ n`:

```
fan-out 400:

  level 1:              400 children
  level 2:          160,000
  level 3:       64,000,000
  level 4:   25,600,000,000 rows
```

Four levels index 25 billion rows. In practice the top levels are permanently cached, so a lookup costs one or two actual disk reads. The complexity is still O(log n) — the base of the logarithm vanishes in big-O — but the base is what makes it usable, which is a good example of big-O hiding something that matters ([`complexity_analysis.md`](../foundations/complexity_analysis.md)).

### Why B+ rather than a hash index

Hash indexes give O(1) equality lookup and are available in some databases, but they cannot do ranges, ordering, or prefix matching — hashing destroys the relationship between a key's value and its location, exactly as in [`hashing.md`](../data_structures/hashing.md). A B+ tree serves equality, ranges, `ORDER BY`, and `MIN`/`MAX` from one structure, which is why it is the default.

## Clustered and secondary indexes

**Clustered index (primary key) — the table itself.** The rows are stored *inside* the primary key's B+ tree leaves, in primary key order. There is no separate heap of data.

```
Leaf of clustered index:   PRIMARY_KEY + all other columns
```

**Secondary index — a separate B+ tree**, ordered by another key. Its leaves do not store the row; they store the indexed column plus a pointer to the row, which in InnoDB is the primary key value.

```
Leaf of secondary index:   indexed_column + PRIMARY_KEY
```

So a lookup through a secondary index takes **two descents**:

```
WHERE email = 'a@b.com'

1. descend the email index  →  finds (email, user_id = 42)
2. descend the clustered index by user_id  →  finds the full row
```

That second step is the **bookmark lookup**, and it is why secondary index scans returning many rows can be slower than a table scan — each matched row costs an extra random read into the primary tree.

**A covering index** avoids it. If every column the query needs is already present in the secondary index's leaf — the indexed columns plus the primary key — the second descent is skipped entirely. Plans report this as "index only scan".

```sql
CREATE INDEX idx ON orders(customer_id, status);

SELECT status FROM orders WHERE customer_id = 7;   -- covered, no row lookup
SELECT total  FROM orders WHERE customer_id = 7;   -- `total` not in the index → lookup
```

Because the clustered index defines physical row order, the choice of primary key matters: a sequential key (auto-increment) appends to the rightmost leaf, while a random key (UUID v4) inserts into random leaves, causing page splits and fragmentation across the whole tree.

## Composite indexes and the leftmost prefix

An index on `(a, b, c)` sorts by `a`, then by `b` within equal `a`, then by `c`. It is usable only for a **leftmost prefix** of those columns.

```
index (a, b, c) can serve:

WHERE a = 1                        ✓
WHERE a = 1 AND b = 2              ✓
WHERE a = 1 AND b = 2 AND c = 3    ✓
WHERE b = 2                        ✗  — b is not a prefix, full scan
WHERE a = 1 AND c = 3              ✓ partially — uses a, then filters c
```

The reason is the sort order. Entries with `b = 2` are scattered throughout the index, because sorting happened on `a` first. Think of a phone book ordered by surname then first name: finding everyone called "James" requires reading the whole book.

A further rule follows: **a range condition stops the index at that column.** In `WHERE a = 1 AND b > 5 AND c = 3`, the index uses `a` and `b`, but `c` cannot be used for seeking, since the entries matching `b > 5` are not sorted by `c` as a group. Put equality columns before range columns when designing the index.

## Why indexes are not free

Each index is a second tree that must be kept in sync, so every `INSERT`, `UPDATE` and `DELETE` writes to all of them. An `UPDATE` touching an indexed column costs a delete plus an insert in that index.

| | Without index | With index |
|---|---|---|
| point lookup | O(n) full scan | O(log n) |
| range query | O(n) | O(log n + matches) |
| insert | 1 write | 1 + one per index |
| storage | rows only | rows + each index's tree |

The trade is the same time-versus-space trade as everywhere else in these notes, with writes as the currency. A write-heavy table with eight indexes can spend more time maintaining indexes than storing data.

## Join algorithms

The optimizer picks among three, and they map directly onto techniques from the other files.

**Nested loop join.** For each row of the outer table, look up matches in the inner one. O(n · m) with no index on the inner side; O(n · log m) with one. Good when the outer side is small.

```
for row in outer:
    for match in inner_index.lookup(row.key):    # the index makes this cheap
        emit(row, match)
```

**Hash join.** Build a hash table on the smaller table's join key, then scan the larger table probing it. O(n + m), the same trick as the seen-before hash map in [`hashing.md`](../data_structures/hashing.md). It needs memory to hold the build side, and it only works for equality joins.

**Merge join.** If both inputs are already sorted on the join key — because an index provides that order — walk them together with two pointers, exactly the merge step from [`sorting.md`](../sorting_and_searching/sorting.md). O(n + m) with no memory overhead, or O(n log n) if a sort is required first.

Reading a plan, the join algorithm chosen tells you what the optimizer believed about the sizes: nested loop means it expected few outer rows, hash join means it expected a large unsorted input.

## Practical consequences when writing queries

**Conditions that disable an index.** Wrapping the indexed column in a function or arithmetic makes the index unusable, because the index stores the column's values, not the function's.

```sql
WHERE YEAR(created_at) = 2024               -- no index use
WHERE created_at >= '2024-01-01'
  AND created_at <  '2025-01-01'            -- index use

WHERE price * 2 > 100                       -- no
WHERE price > 50                            -- yes

WHERE name LIKE '%son'                      -- no: a leading wildcard has no prefix to seek
WHERE name LIKE 'john%'                     -- yes: a prefix range
```

**`SELECT *` prevents covering indexes.** Asking for every column guarantees a row lookup and moves more data than necessary.

**`OR` across different columns** often prevents a single index from being used; the optimizer may rewrite it as a union of two index scans, or give up and scan.

**`LIMIT` with `ORDER BY` on an indexed column** is cheap — the index is already in that order, so the scan stops early. The same `LIMIT` on an unindexed sort must sort everything first.

**`COUNT(*)` on a large table** is O(n) in PostgreSQL, since visibility must be checked per row; approximate counts from statistics are the usual workaround.

**N+1 queries.** Running one query, then one more per returned row, is the application-level version of a nested loop join with no index — and it pays network round-trip latency per iteration. Fetch with a join or an `IN` list instead.

## Pitfalls

- **Indexing everything.** Each index taxes every write. Index for the queries you actually run, which `EXPLAIN` will tell you.
- **Wrong column order in a composite index.** `(a, b)` and `(b, a)` serve different queries; only the leftmost prefix is seekable.
- **Assuming an index will be used.** The optimizer ignores it when selectivity is poor, statistics are stale, or a function wraps the column. Check with `EXPLAIN` rather than assuming.
- **Indexing a low-cardinality column.** An index on a boolean or a two-value status column rarely helps, since half the table matches and a scan is cheaper.
- **Trusting estimated row counts.** Compare against `EXPLAIN ANALYZE`'s actual counts; a large gap explains most bad plans.
- **Random UUID primary keys on a clustered table.** Every insert lands in a random leaf, fragmenting the tree and inflating write cost.
