#include <stack>
using namespace std;

class MinStack {
private:
  stack<int> minst;
  stack<int> st;

public:
  MinStack() {}

  void push(int value) {
    st.push(value);
    int mn = minst.empty() ? value : min(minst.top(), value);
    minst.push(mn);
  }

  void pop() {
    st.pop();
    minst.pop();
  }

  int top() { return st.top(); }

  int getMin() { return minst.top(); }
};
