// Definition of Interval:
// pub struct Interval {
//     pub start: i32,
//     pub end: i32,
// }

impl Solution {
    pub fn can_attend_meetings(mut intervals: Vec<Interval>) -> bool {
        intervals.sort_by_key(|i| i.start);
        intervals.windows(2).all(|w| w[0].end <= w[1].start)
    }
}
