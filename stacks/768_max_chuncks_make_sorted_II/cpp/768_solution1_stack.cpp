#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int maxChunksToSorted(vector<int> &arr) {
    stack<int> st;

    for (int n : arr) {
      if (st.empty() || n > st.top()) {
        st.push(n);
      } else {
        int mx = st.top();
        st.pop();
        while (!st.empty() && n <= st.top())
          st.pop();
        st.push(mx);
      }
    }

    return st.size();
  }
};

// ---- Alternative Compact Version ----
// class Solution {
// public:
//   int maxChunksToSorted(vector<int> &arr) {
//     stack<int> st;
//     for (int x : arr) {
//       int curMax = x;
//       while (!st.empty() && st.top() > x) {
//         curMax = max(curMax, st.top());
//         st.pop();
//       }
//       st.push(curMax);
//     }
//     return st.size();
//   }
// };
