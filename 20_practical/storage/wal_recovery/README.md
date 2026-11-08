# Write-Ahead Log Recovery

A transactional key-value store that survives crashes. The in-memory table is lost in a crash. The "disk" survives: a checkpoint snapshot and an append-only log. In the solution the disk is a plain object, so a crash is simulated by opening a new store on the same disk.

## Stages

1. **Logging.** `begin()`, `set`, `delete`, `get`, `commit` and `abort`. Every operation is appended to the log before it takes effect. A transaction's writes are visible to itself, and to others only after commit.
2. **Recovery.** Opening a store on an existing disk rebuilds the table from the log. Committed transactions are applied. Aborted transactions, and transactions cut off by the crash, are not. Transaction ids must never be reused after recovery.
3. **Checkpoints.** `checkpoint()` saves the committed table to disk and shortens the log, so recovery no longer replays everything since the start. A transaction open during the checkpoint must still be recoverable if it commits afterwards.
4. **Torn writes.** A crash can leave the last log record half written, and a disk can corrupt a record. Detect both, treat everything from the bad record on as never written, and keep the log usable for new records.

## Design notes

- **Redo only.** Uncommitted writes stay in the transaction's buffer and reach the table only at commit (a "no-steal" policy). So the table never holds uncommitted data, and recovery only redoes committed transactions; there is nothing to undo. Databases that write uncommitted changes to disk early (a "steal" policy, as in ARIES) also log the old values and undo uncommitted transactions in reverse log order.
- **The commit point.** A transaction is durable once its `COMMIT` record is in the log. If the crash comes before that record is complete, the transaction did not happen.
- **Transaction ids.** After recovery, new ids start above every id in the log. Otherwise a new transaction could reuse the id of one cut off by the crash, and a later recovery would merge the old, never-committed writes into the new commit. The checkpoint stores the next id for the same reason, since the log it shortens may no longer contain the highest id.
- **Torn and corrupt records.** Each log line carries a CRC32 of its content. Recovery stops at the first line whose checksum does not match, and cuts the log there. Without the cut, new records would be appended after the bad line, and the next recovery would stop at the bad line and lose them.
- **Checkpoint.** The log is shortened to the records of transactions still open, because their `COMMIT` may come later and recovery needs their writes.

## Changes from the original version

The original applied writes only at commit, yet recovery also undid aborted changes, which was never needed. The undo pass also ran in forward log order instead of reverse. Recovery relied on an in-memory table of transaction statuses, which a real crash would lose; the log had no `COMMIT` or `ABORT` records to rebuild it from. There were no checkpoints and no checks for torn records.

## Files

`WalStore.java`: the solution, with checks for each stage in `main`. Run with `java WalStore.java` (Java 21+).
