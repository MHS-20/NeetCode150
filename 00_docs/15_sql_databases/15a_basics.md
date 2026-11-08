# SQL Basics: Selecting, Filtering, Sorting and NULL

A SQL query describes the rows it wants, not the steps to find them. This page covers the parts of a query that work on one table: choosing columns, filtering rows, sorting, limiting, and the rules for `NULL`, the marker for a missing value. `NULL` behaves differently from every other value, and most surprising results in later pages come from it.

Every query in this series was run on PostgreSQL 17, and the results shown are its output. Other databases differ in places, noted where it matters.

## The example schema

All pages use the same four tables: departments, employees, projects, and which employees work on which project.

```sql
CREATE TABLE departments (
    id   integer PRIMARY KEY,
    name text    NOT NULL
);
CREATE TABLE employees (
    id         integer PRIMARY KEY,
    name       text    NOT NULL,
    dept_id    integer REFERENCES departments(id),
    manager_id integer REFERENCES employees(id),
    salary     integer NOT NULL,
    hired      date    NOT NULL
);
CREATE TABLE projects (
    id      integer PRIMARY KEY,
    name    text    NOT NULL,
    dept_id integer REFERENCES departments(id)
);
CREATE TABLE assignments (
    emp_id     integer REFERENCES employees(id),
    project_id integer REFERENCES projects(id),
    hours      integer NOT NULL,
    PRIMARY KEY (emp_id, project_id)
);

INSERT INTO departments VALUES
    (1, 'Engineering'), (2, 'Sales'), (3, 'HR'), (4, 'Legal');
INSERT INTO employees VALUES
    (1, 'Ada', 1,    NULL, 9000, '2019-03-01'),
    (2, 'Bob', 1,    1,    7000, '2020-06-15'),
    (3, 'Cat', 1,    1,    7000, '2021-01-10'),
    (4, 'Dan', 2,    NULL, 6000, '2018-11-05'),
    (5, 'Eve', 2,    4,    5000, '2022-02-20'),
    (6, 'Fay', 3,    NULL, 5500, '2020-09-01'),
    (7, 'Gus', NULL, 1,    4000, '2023-04-12');
INSERT INTO projects VALUES
    (1, 'Search', 1), (2, 'Billing', 1), (3, 'Outreach', 2), (4, 'Audit', 4);
INSERT INTO assignments VALUES
    (1, 1, 10), (2, 1, 20), (2, 2, 15), (3, 2, 30), (5, 3, 25), (7, 1, 5);
```

The data has a few deliberate gaps, used throughout:

- **Gus** has no department (`dept_id` is `NULL`).
- **Legal** has no employees.
- **Fay** and **Dan** have no projects. **Audit** has no one assigned.
- **Ada**, **Dan** and **Fay** have no manager.

```
 id | name | dept_id | manager_id | salary |   hired
----+------+---------+------------+--------+------------
  1 | Ada  |       1 |       NULL |   9000 | 2019-03-01
  2 | Bob  |       1 |          1 |   7000 | 2020-06-15
  3 | Cat  |       1 |          1 |   7000 | 2021-01-10
  4 | Dan  |       2 |       NULL |   6000 | 2018-11-05
  5 | Eve  |       2 |          4 |   5000 | 2022-02-20
  6 | Fay  |       3 |       NULL |   5500 | 2020-09-01
  7 | Gus  |    NULL |          1 |   4000 | 2023-04-12
```

`REFERENCES` declares a **foreign key**: a value that has to exist as a key in another table, or be `NULL`. The database rejects an employee whose `dept_id` is 9, because there is no department 9.

## Choosing columns and filtering rows

```sql
SELECT name, salary
FROM employees
WHERE salary >= 7000
ORDER BY salary DESC, name;
```
```
 name | salary
------+--------
 Ada  |   9000
 Bob  |   7000
 Cat  |   7000
```

- **`SELECT`** lists the columns, or expressions, in the result.
- **`FROM`** names the table.
- **`WHERE`** keeps only the rows for which the condition is true.
- **`ORDER BY`** sorts the result. `DESC` sorts from largest to smallest. Later columns break ties: Bob and Cat both earn 7000, so `name` puts Bob first.

### Conditions

```sql
SELECT name FROM employees
WHERE dept_id IN (1, 3)
  AND hired BETWEEN '2020-01-01' AND '2021-12-31';
```
```
 name
------
 Bob
 Cat
 Fay
```

- `IN (1, 3)` is the same as `dept_id = 1 OR dept_id = 3`.
- `BETWEEN a AND b` includes both ends: it means `>= a AND <= b`.
- `LIKE` matches text patterns. `_` matches exactly one character and `%` matches any number. `name LIKE '_a%'` matches names whose second letter is `a`, here Cat, Dan and Fay.

### Expressions and aliases

```sql
SELECT name, salary * 12 AS yearly
FROM employees
ORDER BY yearly DESC
LIMIT 3;
```
```
 name | yearly
------+--------
 Ada  | 108000
 Cat  |  84000
 Bob  |  84000
```

`AS` names a computed column. `LIMIT 3` keeps the first three rows after sorting.

Cat appears before Bob here, while the earlier query put Bob first. Both earn the same, and this query sorts only by `yearly`, so the order between them is **not defined**. PostgreSQL returned Cat first this time, and could return Bob first on another run or another version. A query that needs a stable order, for example to page through results, has to sort by enough columns to break every tie, such as `ORDER BY yearly DESC, id`.

### `CASE`: a value chosen by conditions

```sql
SELECT name, salary,
       CASE WHEN salary >= 7000 THEN 'high'
            WHEN salary >= 5000 THEN 'mid'
            ELSE 'low' END AS band
FROM employees ORDER BY id;
```
```
 name | salary | band
------+--------+------
 Ada  |   9000 | high
 Bob  |   7000 | high
 Cat  |   7000 | high
 Dan  |   6000 | mid
 Eve  |   5000 | mid
 Fay  |   5500 | mid
 Gus  |   4000 | low
```

The conditions are tried in order, and the first true one decides the value. Without `ELSE`, a row that matches nothing gets `NULL`.

## `NULL`

`NULL` means "no value" or "unknown". It is not zero and not an empty string. Any comparison with `NULL` gives `NULL`, not `true` or `false`:

```sql
SELECT NULL = NULL AS eq, NULL <> 1 AS ne,
       NULL AND false AS and_false, NULL OR true AS or_true;
```
```
  eq  |  ne  | and_false | or_true
------+------+-----------+---------
 NULL | NULL | f         | t
```

SQL uses **three-valued logic**: true, false and unknown (`NULL`). `NULL AND false` is false, because the result is false whatever the unknown value is. `NULL OR true` is true for the same reason. Every other combination with `NULL` stays unknown.

`WHERE` keeps a row only when its condition is **true**. A row whose condition is unknown is dropped, the same as false.

### `= NULL` never matches

```sql
SELECT name FROM employees WHERE dept_id = NULL;
```
```
(0 rows)
```

`dept_id = NULL` is unknown for every row, including Gus's, so no row is kept. Testing for a missing value needs `IS NULL`:

```sql
SELECT name FROM employees WHERE dept_id IS NULL;
```
```
 name
------
 Gus
```

### `<>` drops NULL rows too

```sql
SELECT name FROM employees WHERE dept_id <> 1;
```
```
 name
------
 Dan
 Eve
 Fay
```

Gus is not in department 1, but he is not in the result either. `NULL <> 1` is unknown, so his row is dropped. To treat `NULL` as "a different value", PostgreSQL has `IS DISTINCT FROM`, which compares `NULL` like an ordinary value:

```sql
SELECT name FROM employees WHERE dept_id IS DISTINCT FROM 1;
```
```
 name
------
 Dan
 Eve
 Fay
 Gus
```

### Replacing NULL: `COALESCE`

`COALESCE(a, b, …)` returns its first argument that is not `NULL`:

```sql
SELECT name, COALESCE(dept_id, 0) AS dept FROM employees WHERE id >= 6;
```
```
 name | dept
------+------
 Fay  |    3
 Gus  |    0
```

### NULL in sorting and `DISTINCT`

In PostgreSQL, `NULL` sorts **after** every value in ascending order, and therefore first in descending order:

```sql
SELECT name, dept_id FROM employees ORDER BY dept_id DESC LIMIT 2;
```
```
 name | dept_id
------+---------
 Gus  |    NULL
 Fay  |       3
```

`NULLS FIRST` or `NULLS LAST` after a sort column overrides this. MySQL and SQLite put `NULL` first in ascending order instead, so writing the option explicitly keeps a query's order the same across databases.

`DISTINCT` removes duplicate rows. Here it treats all `NULL`s as equal to each other, so they collapse into one row:

```sql
SELECT DISTINCT dept_id FROM employees ORDER BY dept_id;
```
```
 dept_id
---------
       1
       2
       3
    NULL
```

## The order a query is evaluated in

The clauses are written in one order and evaluated in another:

```
written:     SELECT … FROM … WHERE … GROUP BY … HAVING … ORDER BY … LIMIT
evaluated:   FROM → WHERE → GROUP BY → HAVING → SELECT → ORDER BY → LIMIT
```

This explains which names are visible where. `WHERE` runs before `SELECT`, so it cannot use an alias defined in `SELECT`: `WHERE yearly > 80000` fails with `column "yearly" does not exist`. `ORDER BY` runs after `SELECT`, so it can. `GROUP BY` and `HAVING` are covered in [grouping](15c_grouping.md).
