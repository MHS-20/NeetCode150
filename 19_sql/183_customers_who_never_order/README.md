# 183. Customers Who Never Order

Return the names of customers with no orders, as `Customers`.

`NOT EXISTS` is an anti-join. `NOT IN (SELECT customerId FROM Orders)` returns nothing at all if any `customerId` is `NULL`.

Lesson: [joins](../../00_docs/15_sql_databases/15b_joins.md).
