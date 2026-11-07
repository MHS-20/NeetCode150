#include <stack>
#include <vector>
using namespace std;
class Solution {
public:
  int trap(vector<int> &height) {
    stack<int> st;
    int total = 0;

    for (int i = 0; i < (int)height.size(); i++) {
      while (!st.empty() && height[i] > height[st.top()]) {
        int bottom = st.top();
        st.pop();

        if (st.empty()) {
          break;
        }

        int left = st.top();
        int width = i - left - 1;
        int depth = min(height[left], height[i]) - height[bottom];
        total += width * depth;
      }

      st.push(i);
    }

    return total;
  }
};
