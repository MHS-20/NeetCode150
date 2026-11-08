# SQL Joins

A join combines rows from two tables that belong together, such as an employee and their department. The join condition decides which pairs of rows match. The join type decides what happens to a row that matches nothing: it is dropped, or kept with `NULL`s in place of the missing side. Most join bugs are one of three: the wrong join type, a filter in the wrong clause, or a join that matches one row to several and inflates a total.

The examples use the schema from [basics](15a_basics.md#the-example-schema), and every result shown is PostgreSQL 17's output.

## Inner join: only rows that match

```sql
SELECT e.name, d.name AS dept
FROM employees e
JOIN departments d ON d.id = e.dept_id
ORDER BY e.id;
```
```
 name |    dept
------+-------------
 Ada  | Engineering
 Bob  | Engineering
 Cat  | Engineering
 Dan  | Sales
 Eve  | Sales
 Fay  | HR
```

`e` and `d` are **aliases** for the two tables, so that `e.name` and `d.name` can be told apart. `JOIN` means `INNER JOIN`. For every pair of an employee row and a department row where `d.id = e.dept_id` is true, it outputs one combined row.

Two rows are missing, one from each side:

- **Gus** has `dept_id = NULL`. `d.id = NULL` is never true ([NULL](15a_basics.md#null)), so he matches no department.
- **Legal** has no employee pointing to it.

An inner join keeps only the pairs that match, so both disappear.

## Outer joins: keeping rows that match nothing

### Left join

```sql
SELECT e.name, d.name AS dept
FROM employees e
LEFT JOIN departments d ON d.id = e.dept_id
ORDER BY e.id;
```
```
 name |    dept
------+-------------
 Ada  | Engineering
 ...
 Fay  | HR
 Gus  | NULL
```

A **left join** keeps every row of the **left** table, the one before `LEFT JOIN`. When a left row matches nothing, it appears once with `NULL` in every column of the right table. Gus is back, with no department.

### Right and full join

`RIGHT JOIN` keeps every row of the right table instead. Here Legal appears with `NULL` as the employee name:

```
 name |    dept
------+-------------
 ...
 Fay  | HR
 NULL | Legal
```

`FULL JOIN` keeps unmatched rows from **both** sides: 8 rows, including both Gus with no department and Legal with no employee.

```
 name |    dept
------+-------------
 Ada  | Engineering
 ...
 Fay  | HR
 NULL | Legal
 Gus  | NULL
```

Any right join can be written as a left join by swapping the two tables, and most code uses left joins only, so the table whose rows must all appear is always written first.

### Summary

```
           employees side        departments side
           matched  unmatched    matched  unmatched
INNER        yes       —           yes       —
LEFT         yes      yes (Gus)    yes       —
RIGHT        yes       —           yes      yes (Legal)
FULL         yes      yes          yes      yes
```

## A self-join

A table can be joined to itself, with two aliases for its two roles. `manager_id` points to another row of `employees`:

```sql
SELECT e.name, m.name AS manager
FROM employees e
LEFT JOIN employees m ON m.id = e.manager_id
ORDER BY e.id;
```
```
 name | manager
------+---------
 Ada  | NULL
 Bob  | Ada
 Cat  | Ada
 Dan  | NULL
 Eve  | Dan
 Fay  | NULL
 Gus  | Ada
```

The left join keeps Ada, Dan and Fay, who have no manager. An inner join would drop them. For a manager's manager and further up, a recursive query is needed ([subqueries and CTEs](15d_subqueries_and_ctes.md#recursive-ctes)).

## Joining more than two tables

Each `JOIN` adds one table to the rows built so far. The assignments table links employees and projects:

```sql
SELECT e.name, p.name AS project, a.hours
FROM employees e
JOIN assignments a ON a.emp_id = e.id
JOIN projects p    ON p.id = a.project_id
ORDER BY e.id, p.id;
```
```
 name | project  | hours
------+----------+-------
 Ada  | Search   |    10
 Bob  | Search   |    20
 Bob  | Billing  |    15
 Cat  | Billing  |    30
 Eve  | Outreach |    25
 Gus  | Search   |     5
```

Bob appears twice, once per project. A join outputs one row per matching **pair**, so a row on one side that matches three rows on the other appears three times.

## Cross join

`CROSS JOIN` pairs every row of one table with every row of the other, with no condition. 7 employees and 4 departments give `7 × 4 = 28` rows. It is useful for generating combinations, such as every employee against every month. A join whose `ON` condition is missing or always true produces the same result by accident.

## Filters in `ON` and in `WHERE`

For an inner join, a condition can go in `ON` or in `WHERE` with the same result. For an outer join it cannot.

The task: list every employee, with project 1 if they work on it.

```sql
SELECT e.name, a.project_id
FROM employees e
LEFT JOIN assignments a ON a.emp_id = e.id AND a.project_id = 1
ORDER BY e.id;
```
```
 name | project_id
------+------------
 Ada  |          1
 Bob  |          1
 Cat  |       NULL
 Dan  |       NULL
 Eve  |       NULL
 Fay  |       NULL
 Gus  |          1
```

With the project condition moved to `WHERE`:

```sql
SELECT e.name, a.project_id
FROM employees e
LEFT JOIN assignments a ON a.emp_id = e.id
WHERE a.project_id = 1
ORDER BY e.id;
```
```
 name | project_id
------+------------
 Ada  |          1
 Bob  |          1
 Gus  |          1
```

The four employees without project 1 are gone. The query runs the join first, then `WHERE` ([evaluation order](15a_basics.md#the-order-a-query-is-evaluated-in)). The left join keeps Cat with `project_id = NULL`, and then `WHERE NULL = 1` drops her. A condition on the right table in `WHERE` removes every row that the left join added, which turns it into an inner join with no error or warning.

The rule: a condition that decides **which rows match** goes in `ON`. A condition that decides **which result rows to keep** goes in `WHERE`.

## Rows with no match: anti-joins

"Departments with no employees" is a question about rows that match **nothing**. Two forms give the right answer:

```sql
-- left join, then keep the rows where the right side is missing
SELECT d.name
FROM departments d
LEFT JOIN employees e ON e.dept_id = d.id
WHERE e.id IS NULL;

-- NOT EXISTS
SELECT d.name
FROM departments d
WHERE NOT EXISTS (SELECT 1 FROM employees e WHERE e.dept_id = d.id);
```

Both return `Legal`. The first tests `e.id IS NULL`, on a column that can only be `NULL` when no employee matched, since `id` is a primary key and never `NULL` in a real row.

### The `NOT IN` trap

A third form looks equivalent, but it is not. The task: employees who manage no one.

```sql
SELECT name FROM employees
WHERE id NOT IN (SELECT manager_id FROM employees);
```
```
(0 rows)
```

The answer should be Bob, Cat, Eve, Fay and Gus. The subquery returns the `manager_id` of every employee, which includes `NULL` for Ada, Dan and Fay. `id NOT IN (1, 1, NULL, …)` means `id <> 1 AND … AND id <> NULL`. The last comparison is unknown for every row, so the whole condition is never true, and every row is dropped.

`NOT EXISTS` gives the right answer, because it asks whether a matching row exists and never compares with `NULL`:

```sql
SELECT name FROM employees e
WHERE NOT EXISTS (SELECT 1 FROM employees r WHERE r.manager_id = e.id)
ORDER BY id;
```
```
 name
------
 Bob
 Cat
 Eve
 Fay
 Gus
```

Adding `WHERE manager_id IS NOT NULL` to the `NOT IN` subquery also fixes it. `NOT EXISTS` is the safer default, because it stays correct if a column that never held `NULL` starts to.

## Joins that inflate totals

Joining a table to one with several matching rows repeats each row once per match. A sum over the result then counts some values more than once.

```sql
SELECT d.name, sum(e.salary)
FROM departments d
JOIN employees e   ON e.dept_id = d.id
JOIN assignments a ON a.emp_id = e.id
WHERE d.id = 1
GROUP BY d.name;
```
```
    name     |  sum
-------------+-------
 Engineering | 30000
```

Engineering's real salary total is 23000: Ada 9000, Bob 7000, Cat 7000. The join with assignments repeats Bob, who has two projects, so his 7000 is counted twice. The join was added to filter or count projects, and it silently changed the salary total.

The fix is to aggregate each table at its own level before joining, or to test for projects with `EXISTS` instead of joining. Both are in [subqueries and CTEs](15d_subqueries_and_ctes.md).

## `USING` and natural joins

`JOIN … USING (col)` joins on a column with the same name in both tables, and outputs it once. It is shorter than `ON`, but it only works when the two columns have the same name **and** the same meaning:

```sql
SELECT e.name, d.name
FROM employees e JOIN departments d USING (id)
WHERE e.id <= 2;
```
```
 name |    name
------+-------------
 Ada  | Engineering
 Bob  | Sales
```

This query runs without error and is meaningless: it matches employee 2 with department 2 because both tables call their key `id`. `NATURAL JOIN` goes further and joins on **every** column with a shared name, so adding a column to one table can change what an existing query joins on. Writing the condition with `ON` avoids both problems.
