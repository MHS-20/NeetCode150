# SQL Grouping and Aggregates

An **aggregate** function turns many rows into one value: a count, a sum, an average, a maximum. `GROUP BY` splits the rows into groups first, and the aggregate then produces one value per group. `HAVING` filters the groups after they are formed, in the same way `WHERE` filters rows before.

The examples use the schema from [basics](15a_basics.md#the-example-schema), and every result shown is PostgreSQL 17's output.

## One row per group

```sql
SELECT dept_id,
       count(*)            AS people,
       sum(salary)         AS total,
       avg(salary)::int    AS average,
       max(salary)         AS top
FROM employees
GROUP BY dept_id
ORDER BY dept_id;
```
```
 dept_id | people | total | average | top
---------+--------+-------+---------+------
       1 |      3 | 23000 |    7667 | 9000
       2 |      2 | 11000 |    5500 | 6000
       3 |      1 |  5500 |    5500 | 5500
    NULL |      1 |  4000 |    4000 | 4000
```

`GROUP BY dept_id` puts all rows with the same `dept_id` into one group, and each group becomes one output row. Gus's `NULL` forms a group of its own: grouping treats all `NULL`s as equal, as `DISTINCT` does.

`avg` returns a `numeric` with many decimal places. `::int` converts it to an integer, rounding 7666.67 to 7667.

### Every selected column must be grouped or aggregated

```sql
SELECT dept_id, name FROM employees GROUP BY dept_id;
```
```
ERROR:  column "employees.name" must appear in the GROUP BY clause or be used in an aggregate function
```

Department 1 has three names. The group becomes one row, so there is no single `name` to show. A column in `SELECT` must either be in `GROUP BY`, which makes it the same for the whole group, or be inside an aggregate.

PostgreSQL makes one exception. If the query groups by a table's primary key, it accepts the table's other columns, because the key fixes them. `GROUP BY d.id` allows `SELECT d.name` with no error. MySQL in its default mode applies a similar rule. SQLite accepts any column and picks a value from an arbitrary row of the group, which hides the mistake.

To list the names of each group, an aggregate can join them into one value:

```sql
SELECT dept_id, string_agg(name, ', ' ORDER BY name) AS names
FROM employees GROUP BY dept_id ORDER BY dept_id;
```
```
 dept_id |     names
---------+---------------
       1 | Ada, Bob, Cat
       2 | Dan, Eve
       3 | Fay
    NULL | Gus
```

## Aggregates and NULL

```sql
SELECT count(*)                AS all_rows,
       count(dept_id)          AS with_dept,
       count(DISTINCT dept_id) AS depts,
       count(manager_id)       AS with_mgr
FROM employees;
```
```
 all_rows | with_dept | depts | with_mgr
----------+-----------+-------+----------
        7 |         6 |     3 |        4
```

- **`count(*)`** counts rows.
- **`count(column)`** counts rows where that column is **not** `NULL`. Gus has no `dept_id`, so `count(dept_id)` is 6.
- **`count(DISTINCT column)`** counts different non-`NULL` values.

Every other aggregate also skips `NULL`. The average of 2, `NULL` and 4 is 3, not 2: the `NULL` is left out of both the sum and the count.

On no rows at all, `count` returns 0, but `sum`, `avg`, `max` and `min` return `NULL`:

```sql
SELECT sum(salary) FROM employees WHERE dept_id = 99;     -- NULL
SELECT count(*)    FROM employees WHERE dept_id = 99;     -- 0
```

`COALESCE(sum(salary), 0)` turns the empty sum into 0 where 0 is the right answer.

### `count(*)` after a left join

The task: the number of employees in every department, including Legal with none.

```sql
SELECT d.name, count(*) AS people
FROM departments d
LEFT JOIN employees e ON e.dept_id = d.id
GROUP BY d.id, d.name ORDER BY d.id;
```
```
    name     | people
-------------+--------
 Engineering |      3
 Sales       |      2
 HR          |      1
 Legal       |      1
```

Legal shows 1. The left join keeps Legal as one row, with `NULL` in every employee column, and `count(*)` counts that row. Counting a column of the right table, which is `NULL` exactly on that row, gives the right answer:

```sql
SELECT d.name, count(e.id) AS people ...
```
```
 Legal       |      0
```

## `WHERE` and `HAVING`

`WHERE` filters **rows** before they are grouped. `HAVING` filters **groups** after the aggregates are computed. An aggregate cannot appear in `WHERE`, because when `WHERE` runs no groups exist yet.

```sql
SELECT dept_id, avg(salary)::int AS average
FROM employees
GROUP BY dept_id
HAVING avg(salary) > 5500
ORDER BY dept_id;
```
```
 dept_id | average
---------+---------
       1 |    7667
```

Both in one query:

```sql
SELECT dept_id, count(*)
FROM employees
WHERE salary > 5000
GROUP BY dept_id
HAVING count(*) >= 2
ORDER BY dept_id;
```
```
 dept_id | count
---------+-------
       1 |     3
```

Step by step:

1. `WHERE salary > 5000` drops Eve (5000) and Gus (4000) before grouping.
2. `GROUP BY` forms department 1 with 3 rows, department 2 with 1 (Dan), and department 3 with 1 (Fay).
3. `HAVING count(*) >= 2` keeps only department 1.

Department 2 has two employees in total, but only one is left after `WHERE`. Moving the salary condition changes the answer, so where a condition goes depends on whether it is about single rows or about whole groups.

## Counting a subset: `FILTER`

`FILTER (WHERE …)` makes one aggregate look at a subset of the group's rows, while the other aggregates see all of them:

```sql
SELECT dept_id,
       count(*) FILTER (WHERE salary >= 7000) AS high,
       count(*) AS people
FROM employees GROUP BY dept_id ORDER BY dept_id;
```
```
 dept_id | high | people
---------+------+--------
       1 |    3 |      3
       2 |    0 |      2
       3 |    0 |      1
    NULL |    0 |      1
```

`FILTER` is standard SQL and works in PostgreSQL and SQLite. The portable form, which also works in MySQL, is `sum(CASE WHEN salary >= 7000 THEN 1 ELSE 0 END)`.

## Grouping by an expression

A group key can be computed. `GROUP BY 1` refers to the first column of `SELECT`:

```sql
SELECT extract(year FROM hired) AS year, count(*)
FROM employees GROUP BY 1 ORDER BY 1;
```
```
 year | count
------+-------
 2018 |     1
 2019 |     1
 2020 |     2
 2021 |     1
 2022 |     1
 2023 |     1
```

## Aggregates and window functions

`GROUP BY` collapses each group into one row, so the individual rows are gone. Comparing each employee with their department's average, or numbering rows within a group, needs the rows and the group value side by side. Window functions do that: see [window functions](15e_window_functions.md).
