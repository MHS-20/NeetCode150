# Practical Coding Problems

Exercises for interviews that are not about algorithms: the task is a small program with a spec that grows in stages. The interviewer reveals stage 2 after stage 1 works, and so on. What is judged is whether the code stays correct and easy to extend as the stages arrive: parsing and validation, clear data structures, edge cases, and tests.

Each exercise has:

- `README.md`: the spec, with all its stages. Read one stage at a time to practise as in an interview.
- one solution covering every stage;
- tests grouped by stage, so a later stage cannot silently break an earlier one.

## Business logic (Python)

Payment-company style: transactions, limits, conversions.

| Exercise | Stages |
|---|---|
| [Ledger](business_logic/ledger/) | balances, malformed lines, fees, no overdraft |
| [Rate limiter](business_logic/rate_limiter/) | counting, rolling window, per-endpoint limits, blocking |
| [Currency conversion](business_logic/currency_conversion/) | direct rates, inverse rates, multi-hop, best rate within 3 hops |

Run the tests in an exercise's folder with `python3 test_<name>.py`, or `pytest`.

## Storage (Java)

Database-company style: key-value stores, transactions, caches, on-disk structures. Each solution is a single Java program whose `main` runs the checks: `java <Name>.java` (Java 21+).

| Exercise | Stages |
|---|---|
| [Key-value store with transactions](storage/kv_store_transactions/) | get/set/delete, value counts, nested transactions |
| [LRU cache](storage/lru_cache/) | LRU eviction, time to live, resize |
| [Free page list](storage/free_page_list/) | allocate and free, double-free checks, file growth, statistics |
| [B+ tree](storage/bplus_tree/) | single leaf, splits, range scans, updates |
| [In-memory file system](storage/file_system_tree/) | directories, files, errors, removal and size |
| [MVCC key-value store](storage/mvcc_kv/) | snapshots, deletes, write conflicts, garbage collection |
| [Write-ahead log recovery](storage/wal_recovery/) | logging, crash recovery, checkpoints, torn writes |
