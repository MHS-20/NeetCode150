impl Solution {
    pub fn count_components(n: i32, edges: Vec<Vec<i32>>) -> i32 {
        let mut parent: Vec<usize> = (0..=n as usize).collect();
        let mut count = n;

        for edge in &edges {
            let ra = Self::find(&parent, edge[0] as usize);
            let rb = Self::find(&parent, edge[1] as usize);
            if ra != rb {
                count -= 1;
            }
            parent[rb] = ra;
        }
        count
    }

    fn find(parent: &[usize], mut x: usize) -> usize {
        while parent[x] != x {
            x = parent[x];
        }
        x
    }
}
