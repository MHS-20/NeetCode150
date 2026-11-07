#include <vector>
using namespace std;

class MinStack {
private:
  vector<int> v;
  vector<int> mins;

public:
  MinStack() {}

  void push(int value) {
    v.push_back(value);

    int curmin = mins.empty() ? value : min(mins.back(), value);
    mins.push_back(curmin);
  }

  void pop() {
    v.pop_back();
    mins.pop_back();
  }

  int top() { return v.back(); }

  int getMin() { return mins.back(); }
};
