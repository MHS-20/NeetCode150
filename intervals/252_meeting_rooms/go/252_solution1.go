package intervals

import "slices"

// Definition of Interval:
// type Interval struct {
//     start int
//     end   int
// }

func canAttendMeetings(intervals []Interval) bool {
	slices.SortFunc(intervals, func(a, b Interval) int { return a.start - b.start })
	for i := 0; i < len(intervals)-1; i++ {
		if intervals[i].end > intervals[i+1].start {
			return false
		}
	}
	return true
}
