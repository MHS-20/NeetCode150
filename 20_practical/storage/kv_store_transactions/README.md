# Key-Value Store with Transactions

An in-memory key-value store. Keys and values are strings.

## Stages

1. **Basic operations.** `set(key, value)`, `get(key)` (null if missing) and `delete(key)` (no effect if missing).
2. **Counting.** `count(value)` returns how many keys currently hold `value`, in O(1).
3. **Nested transactions.** `begin()` opens a transaction, and transactions can be nested. `rollback()` undoes every change made since the innermost `begin()`. `commit()` makes the changes of all open transactions permanent and closes them. `rollback()` or `commit()` with no open transaction is an error. Counts must stay correct through rollbacks.

## Design notes

Changes are written to the main map immediately. Each open transaction keeps an undo log holding, for every key it touched, the value before its first change (or "absent"). A rollback replays that log, so it costs O(keys changed); a commit just drops the logs. The alternative, buffering writes per transaction and merging on commit, makes every `get` search all open layers.

## Changes from the original version

The original ran several independent transactions by id, without nesting or value counts, and `get` with an unknown transaction id silently read the committed data instead of failing. This version follows the more common interview form, a single client with nested `BEGIN`/`ROLLBACK`/`COMMIT`.

## Files

`KvStore.java`: the solution, with checks for each stage in `main`. Run with `java KvStore.java` (Java 21+).
