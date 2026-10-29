impl Solution {
    pub fn valid_tree(n: i32, edges: Vec<Vec<i32>>) -> bool {
        let mut count = n;
        let mut parent: Vec<usize> = (0..=n as usize).collect();

        for edge in &edges {
            let ra = Self::find(&parent, edge[0] as usize);
            let rb = Self::find(&parent, edge[1] as usize);
            if ra == rb {
                return false;
            }
            count -= 1;
            parent[rb] = ra;
        }
        count == 1
    }

    fn find(parent: &[usize], mut x: usize) -> usize {
        while parent[x] != x {
            x = parent[x];
        }
        x
    }
}
