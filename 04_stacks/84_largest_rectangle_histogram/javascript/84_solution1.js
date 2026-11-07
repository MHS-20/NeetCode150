class Solution {
  largestRectangleArea(heights) {
    const n = heights.length;
    const st = []; // indices of increasing heights
    let best = 0;

    for (let i = 0; i <= n; i++) {
      const h = i < n ? heights[i] : 0; // sentinel flushes the stack
      while (st.length && heights[st[st.length - 1]] > h) {
        const height = heights[st.pop()];
        const prev = st.length ? st[st.length - 1] : -1;
        best = Math.max(best, height * (i - prev - 1));
      }
      st.push(i);
    }
    return best;
  }
}
