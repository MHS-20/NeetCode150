SELECT t.request_at AS "Day",
       round(avg(CASE WHEN t.status = 'completed' THEN 0 ELSE 1 END), 2) AS "Cancellation Rate"
FROM Trips t
JOIN Users c ON c.users_id = t.client_id AND c.banned = 'No'
JOIN Users d ON d.users_id = t.driver_id AND d.banned = 'No'
WHERE t.request_at BETWEEN '2013-10-01' AND '2013-10-03'
GROUP BY t.request_at
ORDER BY t.request_at;
