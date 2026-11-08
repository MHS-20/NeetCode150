# SQL problems

LeetCode database problems, solved in PostgreSQL. Select PostgreSQL in LeetCode's language menu before submitting: the default is MySQL, and some solutions here use PostgreSQL syntax (`DELETE … USING`, PL/pgSQL functions).

Every solution was run on PostgreSQL 17 with the example data from the problem. The lessons are in [15_sql_databases](../00_docs/15_sql_databases/).

| Problem | Technique | Lesson |
|---|---|---|
| [175. Combine Two Tables](175_combine_two_tables/) | `LEFT JOIN` | [joins](../00_docs/15_sql_databases/15b_joins.md) |
| [176. Second Highest Salary](176_second_highest_salary/) | scalar subquery for `NULL`, `DISTINCT`, `OFFSET` | [subqueries and CTEs](../00_docs/15_sql_databases/15d_subqueries_and_ctes.md) |
| [177. Nth Highest Salary](177_nth_highest_salary/) | PL/pgSQL function, `OFFSET N - 1` | [subqueries and CTEs](../00_docs/15_sql_databases/15d_subqueries_and_ctes.md) |
| [178. Rank Scores](178_rank_scores/) | `dense_rank` | [window functions](../00_docs/15_sql_databases/15e_window_functions.md) |
| [180. Consecutive Numbers](180_consecutive_numbers/) | `lag` twice | [window functions](../00_docs/15_sql_databases/15e_window_functions.md) |
| [181. Employees Earning More Than Their Managers](181_employees_earning_more_than_their_managers/) | self-join | [joins](../00_docs/15_sql_databases/15b_joins.md) |
| [183. Customers Who Never Order](183_customers_who_never_order/) | anti-join with `NOT EXISTS` | [joins](../00_docs/15_sql_databases/15b_joins.md) |
| [184. Department Highest Salary](184_department_highest_salary/) | `rank` per department | [window functions](../00_docs/15_sql_databases/15e_window_functions.md) |
| [185. Department Top Three Salaries](185_department_top_three_salaries/) | `dense_rank() <= 3` per department | [window functions](../00_docs/15_sql_databases/15e_window_functions.md) |
| [196. Delete Duplicate Emails](196_delete_duplicate_emails/) | `DELETE … USING` self-join | [changing data](../00_docs/15_sql_databases/15g_modifying_data_and_transactions.md) |
| [197. Rising Temperature](197_rising_temperature/) | self-join on date minus one day | [joins](../00_docs/15_sql_databases/15b_joins.md) |
| [262. Trips and Users](262_trips_and_users/) | joins as filters, average of a 1/0 flag | [grouping](../00_docs/15_sql_databases/15c_grouping.md) |
