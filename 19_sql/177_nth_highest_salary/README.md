# 177. Nth Highest Salary

Write a function returning the `N`-th highest distinct salary, or `NULL` if there are fewer than `N` distinct salaries.

`OFFSET N - 1` skips the higher salaries. For `N <= 0` a negative offset would be an error in PostgreSQL, so the `CASE` returns `NULL` instead. The wrapping subquery again gives `NULL` instead of no row.

Lesson: [subqueries and CTEs](../../00_docs/15_sql_databases/15d_subqueries_and_ctes.md).
