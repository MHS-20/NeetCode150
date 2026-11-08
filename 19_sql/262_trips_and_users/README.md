# 262. Trips and Users

For each day from 2013-10-01 to 2013-10-03, compute the cancellation rate of trips where neither the client nor the driver is banned, rounded to two decimals, as `Day` and `Cancellation Rate`.

The banned filter is two joins to `Users`. The rate is an average of a 1/0 flag. `avg` of an integer expression returns `numeric` in PostgreSQL, so `round(…, 2)` works directly.

Lesson: [grouping](../../00_docs/15_sql_databases/15c_grouping.md).
