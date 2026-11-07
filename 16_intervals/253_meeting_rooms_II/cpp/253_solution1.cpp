#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
  int minMeetingRooms(vector<Interval> &intervals) {
    int mx = 0;
    priority_queue<int, vector<int>, greater<>> minHeap;

    sort(
        intervals.begin(), intervals.end(),
        [](const Interval &a, const Interval &b) { return a.start < b.start; });

    for (const auto &i : intervals) {
      while (!minHeap.empty() && minHeap.top() <= i.start)
        minHeap.pop();
      minHeap.push(i.end);
      mx = max(mx, (int)minHeap.size());
    }

    return mx;
  }
};
