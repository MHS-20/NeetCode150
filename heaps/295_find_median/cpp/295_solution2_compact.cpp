#include <functional>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
  priority_queue<int> lo;                            // max-heap, lower half
  priority_queue<int, vector<int>, greater<int>> hi; // min-heap, upper half

public:
  void addNum(int num) {
    lo.push(num);
    hi.push(lo.top());
    lo.pop();
    if (hi.size() > lo.size()) {
      lo.push(hi.top());
      hi.pop();
    }
  }

  double findMedian() {
    if (lo.size() > hi.size())
      return lo.top();
    return (lo.top() + hi.top()) / 2.0;
  }
};
