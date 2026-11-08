# 196. Delete Duplicate Emails

Delete duplicate emails, keeping for each email only the row with the smallest `id`.

`DELETE … USING` joins the table with itself: a row is deleted when another row has the same email and a smaller id.

Lesson: [changing data](../../00_docs/15_sql_databases/15g_modifying_data_and_transactions.md).
