/**
 * @param {number[]} arr
 * @return {number}
 */
var maxChunksToSorted = function (arr) {
  const st = [];

  for (const n of arr) {
    if (st.length === 0 || n >= st[st.length - 1]) {
      st.push(n);
    } else {
      const mx = st.pop();
      while (st.length && n < st[st.length - 1]) st.pop();
      st.push(mx);
    }
  }

  return st.length;
};

// ---- Alternative Compact Version ----
// var maxChunksToSorted = function (arr) {
//   const st = []; // max of each chunk, non-decreasing
//   for (const x of arr) {
//     let curMax = x;
//     while (st.length && st[st.length - 1] > x) curMax = Math.max(curMax, st.pop());
//     st.push(curMax);
//   }
//   return st.length;
// };
