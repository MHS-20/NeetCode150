# SQL: Changing Data, Constraints and Transactions

`INSERT`, `UPDATE` and `DELETE` change rows. **Constraints** make the database reject changes that would break a rule, such as a salary below zero or an employee in a department that does not exist. A **transaction** groups several changes so that either all of them happen or none do, and its **isolation level** decides what it sees of other transactions running at the same time.

The examples use the schema from [basics](15a_basics.md#the-example-schema), and every result shown is PostgreSQL 17's output. The concurrency examples were run with two real connections to the same database, labelled A and B.

## Inserting, updating and deleting

```sql
INSERT INTO employees (id, name, dept_id, salary, hired)
VALUES (8, 'Hal', 2, 4500, '2024-05-01')
RETURNING id, name;
```
```
 id | name
----+------
  8 | Hal
```

Listing the columns after the table name makes the insert independent of the table's column order. A column left out gets its default, or `NULL`: Hal's `manager_id` is `NULL`.

`RETURNING` makes `INSERT`, `UPDATE` and `DELETE` return the rows they changed. It saves a second query to read back generated ids or new values. It is a PostgreSQL feature, also in SQLite. MySQL does not have it.

```sql
UPDATE employees SET salary = salary * 1.10
WHERE dept_id = 2
RETURNING name, salary;
```
```
 name | salary
------+--------
 Dan  |   6600
 Eve  |   5500
 Hal  |   4950
```

An `UPDATE` or `DELETE` without `WHERE` changes **every** row of the table. `salary` is an `integer` column, so the result of `* 1.10` is rounded back to an integer when it is stored.

### Updating and deleting with a join

PostgreSQL uses `FROM` in `UPDATE`, and `USING` in `DELETE`, to bring in other tables:

```sql
UPDATE employees e SET salary = salary + 100
FROM departments d
WHERE d.id = e.dept_id AND d.name = 'HR'
RETURNING e.name, e.salary;                 -- Fay | 5600

DELETE FROM assignments a
USING projects p
WHERE p.id = a.project_id AND p.name = 'Billing'
RETURNING a.emp_id, a.project_id;           -- (2, 2) and (3, 2)
```

MySQL writes the same with `UPDATE employees e JOIN departments d ON …`. A subquery in `WHERE`, such as `WHERE dept_id IN (SELECT id FROM departments WHERE name = 'HR')`, works in every database.

## Upsert: `INSERT … ON CONFLICT`

A plain insert of a key that already exists fails:

```sql
INSERT INTO departments VALUES (1, 'Platform');
```
```
ERROR:  duplicate key value violates unique constraint "departments_pkey"
DETAIL:  Key (id)=(1) already exists.
```

`ON CONFLICT` says what to do instead:

```sql
INSERT INTO departments VALUES (1, 'Platform')
ON CONFLICT (id) DO NOTHING;                -- skips the row, no error

INSERT INTO departments VALUES (1, 'Platform'), (5, 'Support')
ON CONFLICT (id) DO UPDATE SET name = EXCLUDED.name
RETURNING *;
```
```
 id |   name
----+----------
  1 | Platform
  5 | Support
```

Department 1 existed, so it was updated. Department 5 did not, so it was inserted. `EXCLUDED` is the row that the insert tried to add.

The conflict target, `(id)` here, must match a unique constraint or unique index. An upsert written as "check whether the row exists, then insert or update" in two statements can fail when two sessions run it at the same time: both find no row, and both insert. `ON CONFLICT` checks and writes in one step. MySQL's equivalent is `INSERT … ON DUPLICATE KEY UPDATE`, and SQLite accepts the PostgreSQL form.

## Constraints

| Constraint | Rule |
|---|---|
| `NOT NULL` | the column must have a value |
| `UNIQUE` | no two rows have the same value (several `NULL`s are allowed) |
| `PRIMARY KEY` | `NOT NULL` and `UNIQUE`; the row's identity |
| `REFERENCES` (foreign key) | the value must exist in the other table, or be `NULL` |
| `CHECK (condition)` | the condition must not be false |

```sql
ALTER TABLE employees ADD CONSTRAINT salary_positive CHECK (salary > 0);
UPDATE employees SET salary = -1 WHERE id = 1;
```
```
ERROR:  new row for relation "employees" violates check constraint "salary_positive"
```

A `CHECK` passes when its condition is true **or `NULL`**. `CHECK (salary > 0)` on a nullable column would accept `NULL`, because `NULL > 0` is unknown, not false.

### Foreign keys and deleting the referenced row

Deleting a department that still has employees fails:

```sql
DELETE FROM departments WHERE id = 3;
```
```
ERROR:  update or delete on table "departments" violates foreign key constraint "employees_dept_id_fkey" on table "employees"
DETAIL:  Key (id)=(3) is still referenced from table "employees".
```

That is the default, `ON DELETE NO ACTION`. The foreign key can declare a different behaviour:

| Option | When the referenced row is deleted |
|---|---|
| `NO ACTION` / `RESTRICT` | the delete fails (the default) |
| `CASCADE` | the referencing rows are deleted too |
| `SET NULL` | the referencing column is set to `NULL` |
| `SET DEFAULT` | the referencing column is set to its default |

`CASCADE` fits rows that cannot exist without their parent, such as an order's line items. It also means one `DELETE` can remove rows from many tables, through chains of cascades, without listing them.

PostgreSQL does not create an index on the referencing column automatically. Without an index on `employees(dept_id)`, every delete from `departments` scans `employees` to check for references.

## Transactions

A transaction starts with `BEGIN` and ends with `COMMIT`, which makes its changes permanent and visible to others, or `ROLLBACK`, which undoes them. Without `BEGIN`, each statement is its own transaction and commits as soon as it finishes.

```sql
BEGIN;
UPDATE employees SET salary = 1 WHERE id = 7;
SELECT salary FROM employees WHERE id = 7;     -- 1, inside the transaction
ROLLBACK;
SELECT salary FROM employees WHERE id = 7;     -- 4000, unchanged
```

Transactions guarantee four properties, called **ACID**:

- **Atomicity:** all of the transaction's changes happen, or none do.
- **Consistency:** constraints hold before and after.
- **Isolation:** concurrent transactions do not see each other's unfinished work, to a degree set by the isolation level.
- **Durability:** once `COMMIT` returns, the changes survive a crash.

### An error aborts the transaction

In PostgreSQL, after any error inside a transaction, every later statement is refused until the transaction ends:

```sql
BEGIN;
UPDATE employees SET salary = salary + 1 WHERE id = 5;
SELECT 1/0;
```
```
ERROR:  division by zero
```
```sql
SELECT salary FROM employees WHERE id = 5;
```
```
ERROR:  current transaction is aborted, commands ignored until end of transaction block
```

`ROLLBACK` is the only way out, and it undoes the update too.

### Savepoints

A **savepoint** marks a point inside a transaction that can be rolled back to without undoing everything:

```sql
BEGIN;
UPDATE employees SET salary = salary + 1 WHERE id = 6;     -- 5501
SAVEPOINT s1;
UPDATE employees SET salary = -5 WHERE id = 6;             -- ERROR: violates salary_positive
ROLLBACK TO SAVEPOINT s1;                                   -- the error is cleared
COMMIT;
SELECT salary FROM employees WHERE id = 6;                  -- 5501
```

The first update survives. Rolling back to the savepoint undoes only what came after it, and also clears the aborted state.

## Isolation levels

Isolation decides what one transaction sees of another transaction's committed changes while it is still running. PostgreSQL offers three levels in practice. Its default is **Read Committed**.

### Read Committed: each statement sees the latest committed data

```
A: BEGIN ISOLATION LEVEL READ COMMITTED
A: SELECT salary FROM employees WHERE id = 1        → 9000
B: UPDATE employees SET salary = 9500 WHERE id = 1  (commits at once)
A: SELECT salary FROM employees WHERE id = 1        → 9500
A: COMMIT
```

The same query, twice in one transaction, returned two different values. This is a **non-repeatable read**. Each statement in Read Committed sees the data committed before **that statement** started.

### Repeatable Read: one snapshot for the whole transaction

```
A: BEGIN ISOLATION LEVEL REPEATABLE READ
A: SELECT salary FROM employees WHERE id = 1        → 9000
B: UPDATE employees SET salary = 9500 WHERE id = 1  (commits)
A: SELECT salary FROM employees WHERE id = 1        → 9000
A: COMMIT
```

A Repeatable Read transaction sees a **snapshot** taken at its first query. B's committed change is invisible to A until A ends.

If A then tries to change a row that B changed after A's snapshot, PostgreSQL refuses:

```
A: BEGIN ISOLATION LEVEL REPEATABLE READ
B: BEGIN ISOLATION LEVEL REPEATABLE READ
A: SELECT salary … → 9000          B: SELECT salary … → 9000
A: UPDATE employees SET salary = salary + 100 WHERE id = 1
A: COMMIT
B: UPDATE employees SET salary = salary + 100 WHERE id = 1
   → ERROR: could not serialize access due to concurrent update
B: ROLLBACK
```

B's snapshot says the salary is 9000, but the row now holds 9100. Applying B's update would silently overwrite A's change, so PostgreSQL makes B fail instead. The application is expected to **retry** B's whole transaction.

**Serializable**, the strictest level, also detects conflicts between transactions that read and write different rows, and guarantees that the result is the same as running the transactions one after another. It reports the same kind of error, which again is handled by retrying.

### Lost updates

A **lost update** happens when two sessions each read a value, compute a new one in the application, and write it back. Both started from the same old value, so one change disappears:

```
A: BEGIN                                    B: BEGIN
A: SELECT salary … → 9000                   B: SELECT salary … → 9000
A: UPDATE … SET salary = 9100 (9000 + 100)
A: COMMIT
                                            B: UPDATE … SET salary = 9100 (9000 + 100)
                                            B: COMMIT
after: 9100                                 expected 9200
```

Read Committed does not prevent this, because each statement is valid on its own. Three fixes:

- **Compute in the database.** `UPDATE … SET salary = salary + 100` reads and writes the row in one statement. If two sessions run it at the same time, the second waits for the first to commit, then applies `+ 100` to the new value. Run that way, the result was 9200.
- **Lock the row when reading it.** `SELECT … FOR UPDATE` locks the selected rows until the transaction ends. In the test, B's `SELECT … FOR UPDATE` waited 1.5 seconds for A to commit, then read 9100, and B's update gave 9200.
- **Use Repeatable Read** and retry on the serialization error shown above.

## Common mistakes

- **`UPDATE` or `DELETE` with a missing or wrong `WHERE`.** Running it inside `BEGIN`, with `RETURNING` to see what changed, leaves the chance to `ROLLBACK`.
- **Check-then-insert in two statements** under concurrency. Use `ON CONFLICT` or a unique constraint.
- **No index on a foreign key column.** Deletes and updates of the referenced table become slow.
- **Read-modify-write in application code** without a lock or a stronger isolation level.
- **Not retrying** Repeatable Read or Serializable transactions after a serialization error.
