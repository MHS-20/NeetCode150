impl Solution {
    pub fn find_redundant_connection(edges: Vec<Vec<i32>>) -> Vec<i32> {
        let n = edges.len();
        let mut parent: Vec<usize> = (0..=n).collect();

        for edge in edges {
            let ra = Self::find(&parent, edge[0] as usize);
            let rb = Self::find(&parent, edge[1] as usize);
            if ra == rb {
                return edge;
            }
            parent[rb] = ra;
        }
        Vec::new()
    }

    fn find(parent: &[usize], mut x: usize) -> usize {
        while parent[x] != x {
            x = parent[x];
        }
        x
    }
}
