struct MedianFinder {
    cnt: [i32; 101],
    below: i32, // numbers < 0
    above: i32, // numbers > 100
    total: i32,
}

impl MedianFinder {
    fn new() -> Self {
        Self { cnt: [0; 101], below: 0, above: 0, total: 0 }
    }

    fn kth(&self, k: i32) -> i32 {
        let mut seen = self.below; // outliers below the range come first in sorted order
        for v in 0..=100 {
            seen += self.cnt[v];
            if seen >= k {
                return v as i32;
            }
        }
        -1
    }

    fn add_num(&mut self, num: i32) {
        if num < 0 {
            self.below += 1;
        } else if num > 100 {
            self.above += 1;
        } else {
            self.cnt[num as usize] += 1;
        }
        self.total += 1;
    }

    fn find_median(&self) -> f64 {
        let a = self.kth((self.total + 1) / 2);
        let b = self.kth(self.total / 2 + 1);
        (a + b) as f64 / 2.0
    }
}
