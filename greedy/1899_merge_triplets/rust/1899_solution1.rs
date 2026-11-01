impl Solution {
    pub fn merge_triplets(triplets: Vec<Vec<i32>>, target: Vec<i32>) -> bool {
        let mut found = [false; 3];

        for t in &triplets {
            if t[0] > target[0] || t[1] > target[1] || t[2] > target[2] {
                continue;
            }
            for i in 0..3 {
                if t[i] == target[i] {
                    found[i] = true;
                }
            }
        }

        found.iter().all(|&f| f)
    }
}
