# Minimum Moves

A grid has empty cells (0) and obstacles (1). From `(0, 0)`, reach `(n-1, m-1)` in the fewest moves. One move goes 1 to `k` cells in a straight line (up, down, left or right), and every cell passed through must be empty and inside the grid. Return -1 if the target cannot be reached.

Example: `k = 2`, grid `[[0, 0], [1, 0]]`. The answer is 2: `(0,0) -> (0,1) -> (1,1)`.

Solution idea: BFS where each cell sends up to `k` cells in each direction. Scanning a direction stops at an obstacle, at the edge, or at a cell already reached with fewer moves, because that cell's own scan covers everything beyond it. Cells reached at the same distance are skipped but the scan continues past them.

Closest LeetCode problem: 2617, Minimum Number of Visited Cells in a Grid. It also jumps several cells per move, but only right or down, and the jump length depends on the cell.
