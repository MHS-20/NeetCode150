# SQL Window Functions

`GROUP BY` collapses each group into one row ([grouping](15c_grouping.md)). A **window function** computes a value over a group of rows, called its **window**, but keeps every row in the result. Each row gets its own value, computed from the rows around it. This answers questions that need a row and its group at the same time: each salary next to its department's average, a rank within each department, a running total, the gap since the previous hire.

The examples use the schema from [basics](15a_basics.md#the-example-schema), and every result shown is PostgreSQL 17's output.

## The `OVER` clause

A function becomes a window function when it is followed by `OVER (…)`. Inside the parentheses:

- **`PARTITION BY`** splits the rows into groups. The function sees only the rows in the current row's partition. Without it, the whole result is one partition.
- **`ORDER BY`** orders the rows inside each partition. Ranking and running totals depend on it.
- **A frame** (`ROWS BETWEEN …`) narrows the window to rows near the current one. It is covered further down.

## An aggregate next to every row

```sql
SELECT name, dept_id, salary,
       avg(salary) OVER (PARTITION BY dept_id)::int          AS dept_avg,
       salary - avg(salary) OVER (PARTITION BY dept_id)::int AS diff
FROM employees
ORDER BY dept_id, id;
```
```
 name | dept_id | salary | dept_avg | diff
------+---------+--------+----------+------
 Ada  |       1 |   9000 |     7667 | 1333
 Bob  |       1 |   7000 |     7667 | -667
 Cat  |       1 |   7000 |     7667 | -667
 Dan  |       2 |   6000 |     5500 |  500
 Eve  |       2 |   5000 |     5500 | -500
 Fay  |       3 |   5500 |     5500 |    0
 Gus  |    NULL |   4000 |     4000 |    0
```

All seven rows are still there. `avg(salary) OVER (PARTITION BY dept_id)` gives each row the average of its department. The same query with `GROUP BY dept_id` would return four rows and lose the names.

## Ranking

Three functions number the rows in order. They differ only when there are ties:

```sql
SELECT name, salary,
       row_number() OVER (ORDER BY salary DESC) AS rn,
       rank()       OVER (ORDER BY salary DESC) AS rnk,
       dense_rank() OVER (ORDER BY salary DESC) AS drnk
FROM employees
ORDER BY salary DESC, id;
```
```
 name | salary | rn | rnk | drnk
------+--------+----+-----+------
 Ada  |   9000 |  1 |   1 |    1
 Bob  |   7000 |  2 |   2 |    2
 Cat  |   7000 |  3 |   2 |    2
 Dan  |   6000 |  4 |   4 |    3
 Fay  |   5500 |  5 |   5 |    4
 Eve  |   5000 |  6 |   6 |    5
 Gus  |   4000 |  7 |   7 |    6
```

- **`row_number`** numbers 1, 2, 3, … with no ties. Bob and Cat both earn 7000, so which of them gets 2 is not defined unless the `ORDER BY` breaks the tie.
- **`rank`** gives tied rows the same number, then skips: Bob and Cat are both 2, and Dan is 4.
- **`dense_rank`** gives tied rows the same number and does not skip: Dan is 3.

### Top N per group

The most common use of ranking: the highest-paid employee in each department. Window functions cannot be used in `WHERE`, because `WHERE` runs before them ([evaluation order](15a_basics.md#the-order-a-query-is-evaluated-in)):

```sql
SELECT name FROM employees WHERE row_number() OVER (ORDER BY salary DESC) <= 2;
```
```
ERROR:  window functions are not allowed in WHERE
```

So the ranking goes in a subquery, and the outer query filters on it:

```sql
SELECT dept_id, name, salary
FROM (
    SELECT *, row_number() OVER (PARTITION BY dept_id
                                 ORDER BY salary DESC, id) AS rn
    FROM employees
) t
WHERE rn = 1
ORDER BY dept_id;
```
```
 dept_id | name | salary
---------+------+--------
       1 | Ada  |   9000
       2 | Dan  |   6000
       3 | Fay  |   5500
    NULL | Gus  |   4000
```

`PARTITION BY dept_id` restarts the numbering in each department. `id` in the `ORDER BY` breaks salary ties, so the result is the same on every run.

Which ranking function to use depends on ties. For "the top 2 salaries in each department", `rank() <= 2` returns all three Engineering employees, because Bob and Cat share second place. `row_number() <= 2` returns exactly two, choosing between Bob and Cat by the tie-breaker.

## Running totals

With `ORDER BY` inside `OVER`, an aggregate covers the rows from the start of the partition up to the current row:

```sql
SELECT name, hired, salary,
       sum(salary) OVER (ORDER BY hired) AS running
FROM employees ORDER BY hired;
```
```
 name |   hired    | salary | running
------+------------+--------+---------
 Dan  | 2018-11-05 |   6000 |    6000
 Ada  | 2019-03-01 |   9000 |   15000
 Bob  | 2020-06-15 |   7000 |   22000
 Fay  | 2020-09-01 |   5500 |   27500
 Cat  | 2021-01-10 |   7000 |   34500
 Eve  | 2022-02-20 |   5000 |   39500
 Gus  | 2023-04-12 |   4000 |   43500
```

Each value is the payroll after that hire. This is a prefix sum computed by the database ([prefix sums](../02_data_structures/2c_prefix_sums.md)).

## Previous and next rows: `lag` and `lead`

`lag(col)` reads `col` from the previous row in the window's order, and `lead(col)` from the next. The first row has no previous row, so `lag` returns `NULL` there:

```sql
SELECT name, hired,
       lag(name)  OVER (ORDER BY hired)         AS prev_hire,
       hired - lag(hired) OVER (ORDER BY hired) AS days_after
FROM employees ORDER BY hired;
```
```
 name |   hired    | prev_hire | days_after
------+------------+-----------+------------
 Dan  | 2018-11-05 | NULL      |       NULL
 Ada  | 2019-03-01 | Dan       |        116
 Bob  | 2020-06-15 | Ada       |        472
 Fay  | 2020-09-01 | Bob       |         78
 Cat  | 2021-01-10 | Fay       |        131
 Eve  | 2022-02-20 | Cat       |        406
 Gus  | 2023-04-12 | Eve       |        416
```

Subtracting two dates in PostgreSQL gives the number of days between them. Without `lag`, comparing a row with the one before it needs a self-join on "the latest earlier row", which is longer and slower.

## Frames

The **frame** is the part of the partition that an aggregate actually reads for the current row. Writing it explicitly:

```sql
SELECT name, salary,
       avg(salary) OVER (ORDER BY hired
                         ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING)::int AS moving
FROM employees ORDER BY hired;
```
```
 name | salary | moving
------+--------+--------
 Dan  |   6000 |   7500
 Ada  |   9000 |   7333
 Bob  |   7000 |   7167
 ...
 Gus  |   4000 |   4500
```

Each value is the average of the row before, the row itself and the row after, in hire order. Dan, the first row, has no row before, so his frame holds two rows: `(6000 + 9000) / 2 = 7500`.

### The default frame and ties

When `OVER` has an `ORDER BY` but no frame, the default frame is `RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW`. `RANGE` counts rows by **value**: every row with the same `ORDER BY` value as the current row, called its **peers**, is included. `ROWS` counts physical rows.

The difference shows up with ties:

```sql
SELECT name, salary,
       sum(salary) OVER (ORDER BY salary) AS range_default,
       sum(salary) OVER (ORDER BY salary
                         ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS rows_frame
FROM employees ORDER BY salary, id;
```
```
 name | salary | range_default | rows_frame
------+--------+---------------+------------
 Gus  |   4000 |          4000 |       4000
 Eve  |   5000 |          9000 |       9000
 Fay  |   5500 |         14500 |      14500
 Dan  |   6000 |         20500 |      20500
 Bob  |   7000 |         34500 |      34500
 Cat  |   7000 |         34500 |      27500
 Ada  |   9000 |         43500 |      43500
```

Bob and Cat both earn 7000. With the default `RANGE` frame, each includes the other, so both get 34500. With `ROWS`, one of them comes first and gets 27500, and the other gets 34500. Which one comes first is not defined, because the `ORDER BY` inside `OVER` does not break the tie. Here PostgreSQL processed Cat first, even though the output is sorted by `id`. A running total over a column with ties should either accept the `RANGE` behaviour or add a tie-breaker, as in `ORDER BY salary, id`.

### `last_value` and the default frame

The default frame also explains a common surprise with `last_value`:

```sql
SELECT name,
       first_value(name) OVER w AS top_in_dept,
       last_value(name)  OVER w AS last_default
FROM employees
WINDOW w AS (PARTITION BY dept_id ORDER BY salary DESC)
ORDER BY dept_id, salary DESC, id;
```
```
 name | top_in_dept | last_default
------+-------------+--------------
 Ada  | Ada         | Ada
 Bob  | Ada         | Cat
 Cat  | Ada         | Cat
 Dan  | Dan         | Dan
 Eve  | Dan         | Eve
 ...
```

`last_value` was expected to return each department's lowest earner. It returns the last row of the **frame**, which by default ends at the current row and its peers. For Ada, the frame is only Ada. For Bob, it is Ada, Bob and his peer Cat. Getting the last row of the whole partition needs the frame `ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING`.

`WINDOW w AS (…)` names a window definition so that several functions can share it.

## When window functions run

Window functions are computed after `WHERE`, `GROUP BY` and `HAVING`, and before `ORDER BY` and `LIMIT`. Two consequences:

- They see only the rows that `WHERE` kept.
- They can be applied to aggregated results: `rank() OVER (ORDER BY sum(salary) DESC)` in a query with `GROUP BY dept_id` ranks departments by total salary.
