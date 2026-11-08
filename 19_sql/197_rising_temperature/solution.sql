SELECT w.id
FROM Weather w
JOIN Weather y ON y.recordDate = w.recordDate - 1
WHERE w.temperature > y.temperature;
