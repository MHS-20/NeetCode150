/**
 * @param {number[]} arr
 * @return {number}
 */
var maxChunksToSorted = function (arr) {
  const st = [];

  for (const n of arr) {
    if (st.length === 0 || n > st[st.length - 1]) {
      st.push(n);
    } else {
      const mx = st.pop();
      while (st.length && n <= st[st.length - 1]) st.pop();
      st.push(mx);
    }
  }

  return st.length;
};
