# Closest Straight City

Each city has a name and integer coordinates `(x, y)`. For every city, find the nearest other city that shares its `x` or its `y` coordinate. Distance is Manhattan distance, `|x1 - x2| + |y1 - y2|`. If several cities are equally near, choose the one whose name comes first alphabetically. If no city shares a coordinate, the answer is `NONE`.

Example: cities `c1 (3, 3)`, `c2 (2, 2)`, `c3 (1, 3)` give `c3, NONE, c1`.

Solution idea: group the cities by `x` and by `y`. Inside one group, sort by the other coordinate. The nearest city in that group is one of the two neighbours in sorted order, so only adjacent pairs are compared. O(n log n).

Closest LeetCode problem: 1779, Find Nearest Point That Has the Same X or Y Coordinate. It uses the same rule for a single query point, where a linear scan is enough.
