# Storage exercises

Database-style exercises in Java. Each folder has a staged spec in its README, and one Java file with the solution for all stages and a `main` that runs checks for each stage. Run one with `java <Name>.java` (Java 21 or later, no build tool).

| Exercise | Stages |
|---|---|
| [Key-value store with transactions](kv_store_transactions/) | get/set/delete, value counts, nested transactions |
| [LRU cache](lru_cache/) | LRU eviction, time to live, resize |
| [Free page list](free_page_list/) | allocate and free, double-free checks, file growth, statistics |
| [B+ tree](bplus_tree/) | single leaf, splits, range scans, updates |
| [In-memory file system](file_system_tree/) | directories, files, errors, removal and size |
| [MVCC key-value store](mvcc_kv/) | snapshots, deletes, write conflicts, garbage collection |
| [Write-ahead log recovery](wal_recovery/) | logging, crash recovery, checkpoints, torn writes |

The exercises started from older Notion notes. Each README ends with what was changed or fixed from that version.
