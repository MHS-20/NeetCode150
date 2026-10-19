struct MedianFinder {
    cnt: [i32; 101],
    total: i32,
}

impl MedianFinder {
    fn new() -> Self {
        Self { cnt: [0; 101], total: 0 }
    }

    // k-th smallest, 1-indexed
    fn kth(&self, k: i32) -> i32 {
        let mut seen = 0;
        for v in 0..=100 {
            seen += self.cnt[v];
            if seen >= k {
                return v as i32;
            }
        }
        -1 // unreachable if 1 <= k <= total
    }

    fn add_num(&mut self, num: i32) {
        self.cnt[num as usize] += 1;
        self.total += 1;
    }

    fn find_median(&self) -> f64 {
        let a = self.kth((self.total + 1) / 2);
        let b = self.kth(self.total / 2 + 1);
        (a + b) as f64 / 2.0
    }
}
