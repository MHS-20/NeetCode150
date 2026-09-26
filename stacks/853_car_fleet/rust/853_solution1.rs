struct Solution;

impl Solution {
    fn car_fleet(target: i32, position: Vec<i32>, speed: Vec<i32>) -> i32 {
        let mut cars: Vec<(i32, i32)> = position.into_iter().zip(speed).collect();
        cars.sort_unstable_by(|a, b| b.0.cmp(&a.0));

        let mut fleets = 0;
        let mut slowest = 0.0; // arrival time of the fleet ahead
        for (p, s) in cars {
            let hours = (target - p) as f64 / s as f64;
            if hours > slowest {
                fleets += 1;
                slowest = hours;
            }
        }
        fleets
    }
}
