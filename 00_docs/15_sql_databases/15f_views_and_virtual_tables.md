# SQL Views and Virtual Tables

A query can read from more than stored tables. A **view** is a saved query that behaves like a table and is recomputed every time it is read. A **materialized view** stores the query's result and has to be refreshed when the data changes. A **temporary table** is a real table that exists only for one session. And several expressions produce rows on the fly: `VALUES`, `generate_series`, and `LATERAL` subqueries.

The examples use the schema from [basics](15a_basics.md#the-example-schema), and every result shown is PostgreSQL 17's output. Each section starts from the original data.

## Views

```sql
CREATE VIEW emp_dept AS
SELECT e.id, e.name, d.name AS dept, e.salary
FROM employees e
LEFT JOIN departments d ON d.id = e.dept_id;

SELECT * FROM emp_dept WHERE salary > 6000 ORDER BY id;
```
```
 id | name |    dept     | salary
----+------+-------------+--------
  1 | Ada  | Engineering |   9000
  2 | Bob  | Engineering |   7000
  3 | Cat  | Engineering |   7000
```

A view stores the **query**, not its rows. Reading the view runs the query against the current data, so a change to `employees` shows up at once:

```sql
UPDATE employees SET salary = 9500 WHERE id = 1;
SELECT name, salary FROM emp_dept WHERE id = 1;
```
```
 name | salary
------+--------
 Ada  |   9500
```

### The planner sees through the view

PostgreSQL replaces the view's name with its query before planning, then plans the combined query as if it had been written out in full. A filter on the view is pushed into the view's query. For `SELECT * FROM emp_dept WHERE id = 3`, the plan looks up employee 3 by its primary key and then its department, without reading the rest of either table:

```
Nested Loop Left Join
  ->  Index Scan using employees_pkey on employees e
        Index Cond: (id = 3)
  ->  Index Scan using departments_pkey on departments d
        Index Cond: (id = e.dept_id)
```

So a view usually costs nothing extra compared with writing its query inline. Its uses are naming a query that many other queries need, and giving a user access to some columns of a table without granting the whole table.

## Updating through a view

A view over **one table**, without grouping, `DISTINCT` or similar, is **automatically updatable** in PostgreSQL: `UPDATE`, `INSERT` and `DELETE` on the view change the underlying table.

```sql
CREATE VIEW eng AS
SELECT id, name, dept_id, salary, hired FROM employees WHERE dept_id = 1;

UPDATE eng SET salary = salary + 100 WHERE id = 2;     -- Bob's salary becomes 7100
```

`emp_dept` joins two tables, so it is not updatable:

```
ERROR:  cannot update view "emp_dept"
DETAIL:  Views that do not select from a single table or view are not automatically updatable.
```

An `INSTEAD OF` trigger can make it updatable by saying what an update should do ([triggers](15h_triggers.md)).

### Inserting rows the view cannot see

An insert through `eng` can add a row that does not satisfy the view's own `WHERE`:

```sql
INSERT INTO eng VALUES (8, 'Hal', 2, 3000, '2024-01-01');
SELECT count(*) FROM eng WHERE id = 8;              -- 0
SELECT name, dept_id FROM employees WHERE id = 8;   -- Hal | 2
```

Hal was inserted into `employees` with department 2, so the Engineering view does not show him. `WITH CHECK OPTION` rejects such rows:

```sql
CREATE VIEW eng_checked AS
SELECT id, name, dept_id, salary, hired FROM employees WHERE dept_id = 1
WITH CHECK OPTION;

INSERT INTO eng_checked VALUES (9, 'Ivy', 2, 3000, '2024-01-01');
```
```
ERROR:  new row violates check option for view "eng_checked"
```

## Materialized views

A **materialized view** runs its query once and stores the result as a table. Reading it is as fast as reading a table, but it does not follow changes:

```sql
CREATE MATERIALIZED VIEW dept_payroll AS
SELECT dept_id, sum(salary) AS total FROM employees GROUP BY dept_id;
```

Starting from Ada at 9500, as after the update above:

```
step                                          dept_payroll, dept 1
CREATE MATERIALIZED VIEW                            23500
UPDATE employees SET salary = 10000 (Ada)           23500     (stale)
REFRESH MATERIALIZED VIEW dept_payroll              24000
```

After the update, the materialized view still shows the old total until `REFRESH` runs the query again. A materialized view suits an expensive query whose result can be a little out of date, such as a dashboard total refreshed every hour.

`REFRESH MATERIALIZED VIEW` locks the view against reads while it runs. `REFRESH MATERIALIZED VIEW CONCURRENTLY` allows reads during the refresh, but requires a unique index on the materialized view.

## Temporary tables

```sql
CREATE TEMP TABLE big_earners AS
SELECT id, name FROM employees WHERE salary >= 7000;
```

A temporary table is a real table, with its rows stored, but it is visible only to the session that created it and is dropped when the session ends. Two sessions can each have their own `big_earners` without conflict. It is useful for intermediate results in a long script, or when a result is read several times and recomputing it would be expensive. Unlike a view, it does not follow later changes to `employees`.

## Rows without a table

### `VALUES`

`VALUES` produces rows from literals and can be used like a table:

```sql
SELECT * FROM (VALUES (1, 'a'), (2, 'b')) AS t(n, letter);
```
```
 n | letter
---+--------
 1 | a
 2 | b
```

It is a quick way to join a short list of values against a table, or to test a query without creating one.

### `generate_series`

`generate_series(1, 3)` returns the rows 1, 2 and 3. It also works with dates and a step, such as one row per day between two dates, which can be left-joined against real data to show the days with nothing recorded. MySQL does not have it. SQLite has it only as an extension: the `sqlite3` command-line shell includes it, but SQLite as embedded in a program, such as Python's `sqlite3` module, usually does not. A recursive CTE does the same job in any of them ([recursive CTEs](15d_subqueries_and_ctes.md#recursive-ctes)).

### `LATERAL`: a subquery per row

A subquery in `FROM` normally cannot refer to the tables before it. With `LATERAL`, it can, and it runs once for each row of those tables. The top two earners of each department:

```sql
SELECT d.name, top.name, top.salary
FROM departments d
CROSS JOIN LATERAL (
    SELECT name, salary FROM employees e
    WHERE e.dept_id = d.id
    ORDER BY salary DESC LIMIT 2
) top
ORDER BY d.id, top.salary DESC, top.name;
```
```
    name     | name | salary
-------------+------+--------
 Engineering | Ada  |   9000
 Engineering | Bob  |   7000
 Sales       | Dan  |   6000
 Sales       | Eve  |   5000
 HR          | Fay  |   5500
```

For each department, the subquery sorts that department's employees and keeps two. Legal has no employees, so its subquery returns no rows, and `CROSS JOIN` drops it. `LEFT JOIN LATERAL (…) ON true` would keep it with `NULL`s.

This is the same "top N per group" as `row_number()` in [window functions](15e_window_functions.md#top-n-per-group). The window version numbers every row of every department and then filters, while the `LATERAL` version asks each department for only two rows.

Bob and Cat tie at 7000 in Engineering, and the subquery's `ORDER BY salary DESC` does not break the tie, so either could be returned as the second row.
