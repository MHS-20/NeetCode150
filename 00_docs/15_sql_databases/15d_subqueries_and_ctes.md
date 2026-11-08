# SQL Subqueries, CTEs and Set Operations

A **subquery** is a query inside another query. It can produce one value to compare against, a yes/no answer for each row, or a whole table to join. A **common table expression** (CTE), written with `WITH`, gives a subquery a name so that the main query reads top to bottom. A recursive CTE can follow a chain of rows, such as an employee's managers, to any depth. Set operations combine the results of two queries.

The examples use the schema from [basics](15a_basics.md#the-example-schema), and every result shown is PostgreSQL 17's output.

## Scalar subqueries: one value

A subquery in parentheses that returns one row and one column can be used anywhere a value can:

```sql
SELECT name, salary
FROM employees
WHERE salary > (SELECT avg(salary) FROM employees)
ORDER BY id;
```
```
 name | salary
------+--------
 Ada  |   9000
 Bob  |   7000
 Cat  |   7000
```

The average salary is about 6214, and three employees earn more.

If the subquery returns more than one row, the query fails when it runs:

```sql
... WHERE salary = (SELECT salary FROM employees WHERE dept_id = 1);
```
```
ERROR:  more than one row returned by a subquery used as an expression
```

Department 1 has three salaries, so there is no single value to compare with. `IN (subquery)` compares against a list instead. If the subquery returns no rows, its value is `NULL`.

## Correlated subqueries

A **correlated** subquery refers to a column of the outer query, so it is evaluated once for each outer row, with that row's values:

```sql
SELECT name, salary, dept_id
FROM employees e
WHERE salary > (SELECT avg(salary) FROM employees x
                WHERE x.dept_id = e.dept_id)
ORDER BY id;
```
```
 name | salary | dept_id
------+--------+---------
 Ada  |   9000 |       1
 Dan  |   6000 |       2
```

For each employee `e`, the subquery computes the average of `e`'s department. Ada earns more than Engineering's 7667, and Dan more than Sales's 5500.

Gus does not appear, and the reason is `NULL`. His `dept_id` is `NULL`, so `x.dept_id = NULL` matches no row, the subquery's average is `NULL`, and `4000 > NULL` is unknown.

A correlated subquery can also produce a column for each row:

```sql
SELECT name,
       (SELECT count(*) FROM assignments a WHERE a.emp_id = e.id) AS projects
FROM employees e ORDER BY id;
```
```
 name | projects
------+----------
 Ada  |        1
 Bob  |        2
 Cat  |        1
 Dan  |        0
 Eve  |        1
 Fay  |        0
 Gus  |        1
```

The planner often turns a correlated subquery into a join, so "once per row" describes the result, not necessarily how it is computed. `EXPLAIN` shows what it actually does ([query planning](15i_query_planning_and_indexes.md)).

## `EXISTS`: does a matching row exist

```sql
SELECT name FROM employees e
WHERE EXISTS (SELECT 1 FROM assignments a WHERE a.emp_id = e.id)
ORDER BY id;
```
```
 name
------
 Ada
 Bob
 Cat
 Eve
 Gus
```

`EXISTS` is true when the subquery returns at least one row. Its columns are never read, which is why `SELECT 1` is the usual way to write it. Bob has two projects and still appears once. A join with `assignments` would list him twice, which is the row duplication shown in [joins](15b_joins.md#joins-that-inflate-totals). `NOT EXISTS` and its advantage over `NOT IN` are also covered there.

## Derived tables: a subquery in `FROM`

A subquery in `FROM` acts as a temporary table for the rest of the query. It must have an alias:

```sql
SELECT d.name, t.total
FROM departments d
JOIN (SELECT dept_id, sum(salary) AS total
      FROM employees GROUP BY dept_id) t ON t.dept_id = d.id
ORDER BY d.id;
```
```
    name     | total
-------------+-------
 Engineering | 23000
 Sales       | 11000
 HR          |  5500
```

Grouping **inside** the subquery is the fix for the inflated total in [joins](15b_joins.md#joins-that-inflate-totals): each table is aggregated to one row per department before the join, so no row is repeated.

## CTEs: naming subqueries with `WITH`

A CTE defines one or more named queries before the main query. The derived table above, with a second total added:

```sql
WITH dept_totals AS (
    SELECT dept_id, sum(salary) AS total
    FROM employees GROUP BY dept_id
),
dept_hours AS (
    SELECT e.dept_id, sum(a.hours) AS hours
    FROM employees e JOIN assignments a ON a.emp_id = e.id
    GROUP BY e.dept_id
)
SELECT d.name, t.total, COALESCE(h.hours, 0) AS hours
FROM departments d
JOIN dept_totals t     ON t.dept_id = d.id
LEFT JOIN dept_hours h ON h.dept_id = d.id
ORDER BY d.id;
```
```
    name     | total | hours
-------------+-------+-------
 Engineering | 23000 |    75
 Sales       | 11000 |    25
 HR          |  5500 |     0
```

Salaries and hours are each summed at their own level and then joined one row per department, so Engineering's total stays 23000, not the 30000 of the direct join.

A CTE is mainly about readability: each step has a name, and a later CTE can use an earlier one.

### Does PostgreSQL compute a CTE separately?

Since PostgreSQL 12, a CTE that is used once and has no side effects is folded into the main query, like a subquery. The planner can then push conditions into it. With `WHERE id = 3` on a CTE over `employees`, the plan is a single index lookup:

```
Index Scan using employees_pkey on employees
  Index Cond: (id = 3)
```

`AS MATERIALIZED` forces the CTE to be computed in full first. The same query then reads the whole table and filters afterwards:

```
CTE Scan on t
  Filter: (id = 3)
  CTE t
    ->  Seq Scan on employees
```

Materializing helps when an expensive CTE is used several times, and hurts when a filter outside could have cut it down. Versions before 12 always materialized.

## Recursive CTEs

`WITH RECURSIVE` defines a query in terms of itself. It has two parts joined by `UNION ALL`:

- the **anchor**, a normal query that gives the starting rows;
- the **recursive part**, which refers to the CTE's own name and produces new rows from the rows found in the previous round.

The database runs the anchor, then runs the recursive part on the new rows, again and again, until a round produces no rows.

The simplest example counts from 1 to 5:

```sql
WITH RECURSIVE n(i) AS (
    SELECT 1                              -- anchor
    UNION ALL
    SELECT i + 1 FROM n WHERE i < 5       -- recursive part
)
SELECT i FROM n;
```

This returns 1, 2, 3, 4, 5. The condition `i < 5` stops it. Without a stop condition the query runs forever.

### Walking a hierarchy

Every employee's level in the management tree, starting from the people with no manager:

```sql
WITH RECURSIVE chain AS (
    SELECT id, name, manager_id, 0 AS depth
    FROM employees WHERE manager_id IS NULL                  -- anchor: the top
    UNION ALL
    SELECT e.id, e.name, e.manager_id, c.depth + 1
    FROM employees e JOIN chain c ON e.manager_id = c.id     -- one level down
)
SELECT name, depth FROM chain ORDER BY depth, id;
```
```
 name | depth
------+-------
 Ada  |     0
 Dan  |     0
 Fay  |     0
 Bob  |     1
 Cat  |     1
 Eve  |     1
 Gus  |     1
```

Round 1 (the anchor) finds Ada, Dan and Fay. Round 2 finds everyone whose manager was found in round 1. Round 3 finds no one, so the recursion stops.

Going **up** instead, from one employee to the top, builds a path:

```sql
WITH RECURSIVE up AS (
    SELECT id, name, manager_id, name::text AS path
    FROM employees WHERE id = 5
    UNION ALL
    SELECT m.id, m.name, m.manager_id, up.path || ' -> ' || m.name
    FROM employees m JOIN up ON m.id = up.manager_id
)
SELECT path FROM up WHERE manager_id IS NULL;
```
```
    path
------------
 Eve -> Dan
```

This is a BFS over the rows, one level per round ([graphs](../11_graphs/11a_graphs_bfs_dfs.md)). On data with a cycle, such as two employees who manage each other, it never stops. PostgreSQL 14 added a `CYCLE` clause to detect that. Using `UNION` instead of `UNION ALL` also stops it when a round produces only rows that were already found.

## Set operations

Set operations combine the rows of two queries with the same number of columns:

| Operation | Result |
|---|---|
| `UNION` | rows in either result, duplicates removed |
| `UNION ALL` | rows in either result, duplicates kept |
| `INTERSECT` | rows in both results |
| `EXCEPT` | rows in the first result but not the second |

```sql
SELECT name FROM employees WHERE dept_id = 1
UNION
SELECT name FROM employees WHERE salary < 5000
ORDER BY 1;
```
```
 name
------
 Ada
 Bob
 Cat
 Gus
```

`UNION` removes duplicates, which takes a sort or a hash over the whole result. `UNION ALL` skips that, so it is the one to use when duplicates are impossible or wanted.

```sql
SELECT id FROM departments EXCEPT SELECT dept_id FROM employees;
```
```
 id
----
  4
```

Department 4, Legal, has no employees. The right side contains `NULL` from Gus, yet `EXCEPT` still returns 4. Set operations treat `NULL`s as equal to each other, as `DISTINCT` does, so they are not affected by the `NULL` problem of [`NOT IN`](15b_joins.md#the-not-in-trap).
