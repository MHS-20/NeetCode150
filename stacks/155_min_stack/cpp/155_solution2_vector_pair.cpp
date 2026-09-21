#include <vector>
using namespace std;

class MinStack {
private:
  vector<pair<int, int>>
      st; // {value, minimum of everything up to and including it}

public:
  MinStack() {}

  void push(int value) {
    int curMin = st.empty() ? value : min(st.back().second, value);
    st.push_back({value, curMin});
  }

  void pop() { st.pop_back(); }

  int top() { return st.back().first; }

  int getMin() { return st.back().second; }
};
