# SQL Triggers

A **trigger** runs a function automatically when rows of a table are inserted, updated or deleted. It can record the change in an audit table, clean up or reject the new values, or keep another table in step. The work happens inside the same statement and transaction as the change that fired it, so it cannot be skipped by a caller that forgets. The same property is the cost: every write to the table now does extra work that the statement does not show.

The examples use the schema from [basics](15a_basics.md#the-example-schema), and every result shown is PostgreSQL 17's output. PostgreSQL triggers call a function, written here in PL/pgSQL, PostgreSQL's procedural language. MySQL and SQLite put the trigger body directly in `CREATE TRIGGER` instead.

## The parts of a trigger

```sql
CREATE TRIGGER name
{BEFORE | AFTER | INSTEAD OF} {INSERT | UPDATE | DELETE} ON table
FOR EACH {ROW | STATEMENT}
EXECUTE FUNCTION some_function();
```

- **`BEFORE`** runs before the row is written. The function can change the new row or cancel the write.
- **`AFTER`** runs after the row is written. It sees the final values, and is used to react to the change.
- **`INSTEAD OF`** replaces the operation. It is only allowed on views.
- **`FOR EACH ROW`** runs once per changed row. **`FOR EACH STATEMENT`** runs once per statement, even if it changed no rows.

Inside a row-level trigger function, `NEW` is the row being written and `OLD` is the row before the change. `INSERT` has only `NEW`, and `DELETE` only `OLD`. `TG_OP` holds `'INSERT'`, `'UPDATE'` or `'DELETE'`.

## An audit log: `AFTER UPDATE`

Every salary change is recorded with its old and new value:

```sql
CREATE TABLE salary_log (
    emp_id     int,
    old_salary int,
    new_salary int,
    changed_at timestamptz DEFAULT now()
);

CREATE FUNCTION log_salary() RETURNS trigger LANGUAGE plpgsql AS $$
BEGIN
  IF NEW.salary IS DISTINCT FROM OLD.salary THEN
    INSERT INTO salary_log (emp_id, old_salary, new_salary)
    VALUES (OLD.id, OLD.salary, NEW.salary);
  END IF;
  RETURN NULL;          -- ignored for AFTER triggers
END $$;

CREATE TRIGGER salary_audit
AFTER UPDATE ON employees
FOR EACH ROW EXECUTE FUNCTION log_salary();
```

```sql
UPDATE employees SET salary = salary + 500 WHERE dept_id = 1;
UPDATE employees SET name = 'Eva' WHERE id = 5;
SELECT emp_id, old_salary, new_salary FROM salary_log ORDER BY emp_id;
```
```
 emp_id | old_salary | new_salary
--------+------------+------------
      1 |       9000 |       9500
      2 |       7000 |       7500
      3 |       7000 |       7500
```

The first update changed three rows, so the trigger ran three times and wrote three log rows. The second update also fired the trigger, for Eve's row, but the `IF` skipped it because her salary did not change. `IS DISTINCT FROM` is used instead of `<>` so that a change from or to `NULL` is still detected ([NULL](15a_basics.md#null)).

`changed_at` uses `now()`, which in PostgreSQL is the start time of the **transaction**. All rows logged by one transaction get the same time.

## Cleaning and rejecting rows: `BEFORE`

A `BEFORE` row trigger can change `NEW` before it is stored, or raise an error to stop the write:

```sql
CREATE FUNCTION clean_employee() RETURNS trigger LANGUAGE plpgsql AS $$
BEGIN
  NEW.name := initcap(trim(NEW.name));
  IF NEW.manager_id = NEW.id THEN
    RAISE EXCEPTION 'employee % cannot manage themselves', NEW.id;
  END IF;
  RETURN NEW;           -- the row to write
END $$;

CREATE TRIGGER employee_clean
BEFORE INSERT OR UPDATE ON employees
FOR EACH ROW EXECUTE FUNCTION clean_employee();
```

```sql
INSERT INTO employees VALUES (8, '  hal  ', 2, NULL, 4500, '2024-05-01');
SELECT id, name FROM employees WHERE id = 8;     -- 8 | Hal
UPDATE employees SET manager_id = 3 WHERE id = 3;
```
```
ERROR:  employee 3 cannot manage themselves
```

The name was stored as `Hal`: spaces trimmed, first letter capitalised. The second statement was rejected, and the error rolls back the whole statement.

A `BEFORE` row trigger's return value decides what happens to the row:

- returning `NEW`, possibly changed, writes it;
- returning `NULL` **silently skips** the row, with no error.

A `BEFORE` trigger that returns `NULL` by mistake makes inserts appear to succeed while storing nothing.

The self-management rule could also be a constraint, `CHECK (manager_id <> id)`, which is shorter and visible in the table's definition. A trigger is needed when the rule depends on other rows or other tables, which a `CHECK` cannot read.

## Keeping a derived value in step

`departments` gets a `headcount` column, kept equal to the number of employees in each department:

```sql
ALTER TABLE departments ADD COLUMN headcount int NOT NULL DEFAULT 0;
UPDATE departments d
SET headcount = (SELECT count(*) FROM employees e WHERE e.dept_id = d.id);

CREATE FUNCTION keep_headcount() RETURNS trigger LANGUAGE plpgsql AS $$
BEGIN
  IF TG_OP IN ('UPDATE', 'DELETE') AND OLD.dept_id IS NOT NULL THEN
    UPDATE departments SET headcount = headcount - 1 WHERE id = OLD.dept_id;
  END IF;
  IF TG_OP IN ('INSERT', 'UPDATE') AND NEW.dept_id IS NOT NULL THEN
    UPDATE departments SET headcount = headcount + 1 WHERE id = NEW.dept_id;
  END IF;
  RETURN NULL;
END $$;

CREATE TRIGGER headcount
AFTER INSERT OR DELETE OR UPDATE OF dept_id ON employees
FOR EACH ROW EXECUTE FUNCTION keep_headcount();
```

`UPDATE OF dept_id` fires the trigger only for updates that set `dept_id`, so salary changes do not run it. A move between departments is one decrement and one increment.

With Hal from the previous example in Sales:

```
change                                     Eng  Sales  HR  Legal
start                                       3     3     1    0
UPDATE employees SET dept_id = 4 (Gus)      3     3     1    1
DELETE FROM employees WHERE id = 8 (Hal)    3     2     1    1
```

Gus had no department, so moving him only incremented Legal.

The counter makes "employees per department" a single column read instead of a `count(*)` with a join. In exchange, every insert, delete and department change on `employees` also updates a row of `departments`. Two transactions that add employees to the same department both update that department's row, so the second waits for the first to commit.

## Statement-level triggers

A `FOR EACH STATEMENT` trigger runs once per statement. With a **transition table** (`REFERENCING NEW TABLE AS …`), it can read all the rows the statement changed at once:

```sql
CREATE TABLE stmt_log (op text, rows_seen int);

CREATE FUNCTION log_stmt() RETURNS trigger LANGUAGE plpgsql AS $$
BEGIN
  INSERT INTO stmt_log VALUES (TG_OP, (SELECT count(*) FROM changed));
  RETURN NULL;
END $$;

CREATE TRIGGER per_statement
AFTER UPDATE ON employees
REFERENCING NEW TABLE AS changed
FOR EACH STATEMENT EXECUTE FUNCTION log_stmt();
```

```sql
UPDATE employees SET salary = salary + 1;                    -- 7 rows
UPDATE employees SET salary = salary + 1 WHERE id = 999;     -- 0 rows
SELECT * FROM stmt_log;
```
```
   op   | rows_seen
--------+-----------
 UPDATE |         7
 UPDATE |         0
```

The trigger ran once for each statement, including the one that matched no rows. The row-level audit trigger from earlier ran 7 times for the first statement, once per row, and wrote 7 log rows. For bulk changes, one statement-level trigger that processes the transition table in a single query does far less work than a row trigger firing once per row.

## `INSTEAD OF`: making a view updatable

A view over a join cannot be updated directly ([views](15f_views_and_virtual_tables.md#updating-through-a-view)). An `INSTEAD OF` trigger says what an update of the view means:

```sql
CREATE VIEW emp_dept AS
SELECT e.id, e.name, d.name AS dept
FROM employees e LEFT JOIN departments d ON d.id = e.dept_id;

CREATE FUNCTION emp_dept_update() RETURNS trigger LANGUAGE plpgsql AS $$
BEGIN
  UPDATE employees
  SET name    = NEW.name,
      dept_id = (SELECT id FROM departments WHERE name = NEW.dept)
  WHERE id = OLD.id;
  RETURN NEW;
END $$;

CREATE TRIGGER emp_dept_upd
INSTEAD OF UPDATE ON emp_dept
FOR EACH ROW EXECUTE FUNCTION emp_dept_update();

UPDATE emp_dept SET dept = 'Sales' WHERE id = 6;
SELECT * FROM emp_dept WHERE id = 6;
```
```
 id | name | dept
----+------+-------
  6 | Fay  | Sales
```

Setting `dept` on the view becomes an update of `employees.dept_id`. That update in turn fired the `headcount` trigger on `employees`: HR went from 1 to 0, and Sales from 2 to 3. One statement on the view ran two triggers on two tables, and nothing in the `UPDATE` itself shows it.

## Triggers that fire themselves

A trigger on `employees` that updates `employees` fires itself again:

```sql
CREATE FUNCTION bump() RETURNS trigger LANGUAGE plpgsql AS $$
BEGIN
  UPDATE employees SET salary = salary + 1 WHERE id = NEW.id;
  RETURN NULL;
END $$;

CREATE TRIGGER bump AFTER UPDATE ON employees
FOR EACH ROW EXECUTE FUNCTION bump();

UPDATE employees SET salary = 1 WHERE id = 1;
```
```
ERROR:  stack depth limit exceeded
```

Each update fires the trigger, which runs another update, which fires the trigger again, until PostgreSQL runs out of stack. The error rolls back everything. A trigger that has to write to its own table needs a condition that stops it, such as checking `pg_trigger_depth()`, or a `WHEN` clause on the trigger that is false for its own updates. Usually the better fix is a `BEFORE` trigger that changes `NEW` directly, which writes the row once and does not run another `UPDATE`.

## When a trigger is the wrong tool

| Need | Simpler tool |
|---|---|
| a value computed from other columns of the same row | a **generated column** |
| a rule on one row's values | a `CHECK` constraint |
| a value must exist in another table | a foreign key |
| delete child rows with their parent | `ON DELETE CASCADE` |
| a summary that may be slightly stale | a materialized view |

A generated column, for example:

```sql
ALTER TABLE employees ADD COLUMN yearly int
GENERATED ALWAYS AS (salary * 12) STORED;
```

`yearly` is recomputed on every insert and update and cannot be written directly. Ada's `yearly` was 108000, and after setting her salary to 10000 it became 120000 with no trigger.

These declarations are part of the table's definition, where anyone reading the schema sees them. A trigger's behaviour lives in a function, and its effects do not appear in the statements that cause them.

## The costs of triggers

- **Hidden work.** An `UPDATE` that looks like it touches one table can write to several, as the `INSTEAD OF` example shows. Reading the statement alone does not reveal it.
- **Bulk writes slow down.** A row trigger runs once per row. Loading a million rows runs it a million times.
- **Chains and loops.** Triggers that change tables with their own triggers can fire each other, or themselves.
- **Contention.** Triggers that update a shared summary row make concurrent transactions wait on that row.
- **Order.** Several triggers for the same event on the same table run in alphabetical order of their names in PostgreSQL. Renaming a trigger can change the order.
