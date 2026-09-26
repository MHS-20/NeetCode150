class Solution {
public:
  vector<int> dailyTemperatures(vector<int> &temps) {
    stack<int> st;
    vector<int> res(temps.size());

    for (int i = 0; i < temps.size(); i++) {
      while (!st.empty() && temps[i] > temps[st.top()]) {
        res[st.top()] = i - st.top();
        st.pop();
      }
      st.push(i);
    }

    return res;
  }
};
