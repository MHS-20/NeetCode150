class Solution {
  dailyTemperatures(temps) {
    const res = new Array(temps.length).fill(0);
    const st = []; // indices with no warmer day yet

    for (let i = 0; i < temps.length; i++) {
      while (st.length && temps[i] > temps[st[st.length - 1]]) {
        const j = st.pop();
        res[j] = i - j;
      }
      st.push(i);
    }
    return res;
  }
}
