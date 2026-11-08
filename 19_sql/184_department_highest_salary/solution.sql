SELECT d.name AS Department, t.name AS Employee, t.salary AS Salary
FROM (
    SELECT name, salary, departmentId,
           rank() OVER (PARTITION BY departmentId ORDER BY salary DESC) AS rnk
    FROM Employee
) t
JOIN Department d ON d.id = t.departmentId
WHERE t.rnk = 1;
