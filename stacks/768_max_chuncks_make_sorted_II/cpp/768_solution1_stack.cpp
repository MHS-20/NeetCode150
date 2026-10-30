#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int maxChunksToSorted(vector<int> &arr) {
    vector<int> st; // max of each chunk, non-decreasing
    for (int x : arr) {
      int curMax = x;
      while (!st.empty() && st.back() > x) {
        curMax = max(curMax, st.back());
        st.pop_back();
      }
      st.push_back(curMax);
    }
    return st.size();
  }
};
