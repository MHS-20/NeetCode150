# MVCC Key-Value Store

A key-value store where transactions read from a consistent snapshot while other transactions write, as in PostgreSQL's Repeatable Read level.

## Stages

1. **Snapshots.** `begin()` returns a transaction with `get`, `put`, `commit` and `rollback`. A transaction sees the data committed before it began, plus its own writes. Changes committed later stay invisible to it. A transaction cannot be used after it ends.
2. **Deletes.** `delete(key)`. A transaction that began before the delete still sees the key.
3. **Write conflicts.** If two concurrent transactions write the same key, the one that commits second fails and is aborted. Transactions writing different keys both commit.
4. **Garbage collection.** `garbageCollect()` removes versions that no open or future transaction can read, and removes deleted keys entirely once every snapshot sees the deletion.

## Design notes

Each key keeps its versions, oldest first, each stamped with a commit timestamp; a delete is a version with no value (a tombstone). A snapshot is just a timestamp: a read returns the newest version at or before it. Writes are buffered in the transaction and turned into versions at commit, so other transactions never see uncommitted data.

The conflict check at commit is "first committer wins". Without it, two transactions that both read a balance of 100 and add 10 and 20 would both commit, and one update would be lost. With it, the second one fails and the caller retries. The same error appears in PostgreSQL under Repeatable Read, as `could not serialize access due to concurrent update`.

Garbage collection keeps, for each key, the newest version visible to the oldest open snapshot, and everything newer. Anything older can never be read again. A long-running transaction therefore holds back garbage collection for the whole store.

## Changes from the original version

The original used one counter for both transaction ids and commit versions, and did not check for conflicts, so concurrent updates to the same key were silently lost. It had no deletes and no garbage collection.

## Files

`MvccStore.java`: the solution, with checks for each stage in `main`. Run with `java MvccStore.java` (Java 21+).
