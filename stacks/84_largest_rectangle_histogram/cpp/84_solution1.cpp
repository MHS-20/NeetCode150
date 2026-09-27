class Solution {
public:
  int largestRectangleArea(vector<int> &heights) {
    int maxArea = 0;
    stack<int> st;

    for (int i = 0; i < heights.size(); i++) {
      while (!st.empty() && heights[st.top()] > heights[i]) {
        int idx = st.top();
        st.pop();

        int prev = st.empty() ? -1 : st.top();
        int width = (i - 1) - (prev + 1) + 1;
        int newArea = heights[idx] * width;
        maxArea = max(maxArea, newArea);
      }
      st.push(i);
    }

    while (!st.empty()) {
      int idx = st.top();
      st.pop();
      int prev = st.empty() ? -1 : st.top();
      int newArea = heights[idx] * (heights.size() - prev - 1);
      maxArea = max(maxArea, newArea);
    }

    return maxArea;
  }
};
