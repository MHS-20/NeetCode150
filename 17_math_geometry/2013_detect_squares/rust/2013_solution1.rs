use std::collections::HashMap;

struct DetectSquares {
    cnt: HashMap<(i32, i32), i32>,
}

impl DetectSquares {
    fn new() -> Self {
        DetectSquares { cnt: HashMap::new() }
    }

    fn get(&self, x: i32, y: i32) -> i32 {
        *self.cnt.get(&(x, y)).unwrap_or(&0)
    }

    fn add(&mut self, point: Vec<i32>) {
        *self.cnt.entry((point[0], point[1])).or_insert(0) += 1;
    }

    fn count(&self, point: Vec<i32>) -> i32 {
        let (x, y) = (point[0], point[1]);
        let mut res = 0;

        for (&(px, py), &c) in &self.cnt {
            if px == x || (px - x).abs() != (py - y).abs() {
                continue; // must be a diagonal corner with side length > 0
            }
            res += c * self.get(x, py) * self.get(px, y);
        }
        res
    }
}
