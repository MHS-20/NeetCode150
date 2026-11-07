impl Solution {
    pub fn min_cost_connect_points(points: Vec<Vec<i32>>) -> i32 {
        let n = points.len();
        let mut min_cost = vec![i32::MAX; n];
        let mut in_tree = vec![false; n];
        min_cost[0] = 0;
        let mut cost = 0;

        for _ in 0..n {
            // 1. Pick the cheapest point not yet in the tree
            let u = (0..n)
                .filter(|&i| !in_tree[i])
                .min_by_key(|&i| min_cost[i])
                .unwrap();

            // 2. Add it
            in_tree[u] = true;
            cost += min_cost[u];

            // 3. Update the outside points' best connection
            for i in 0..n {
                if in_tree[i] {
                    continue;
                }
                let dist = (points[i][0] - points[u][0]).abs() + (points[i][1] - points[u][1]).abs();
                min_cost[i] = min_cost[i].min(dist);
            }
        }
        cost
    }
}
