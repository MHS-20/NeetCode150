DELETE FROM Person p
USING Person q
WHERE p.email = q.email AND p.id > q.id;
