# 197. Rising Temperature

Return the ids of days warmer than the previous calendar day.

The previous day is matched by date, `w.recordDate - 1`, not by the previous row: a missing day must not count as "yesterday". `lag` would compare with the previous row even across a gap.

Lesson: [joins](../../00_docs/15_sql_databases/15b_joins.md).
