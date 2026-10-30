/**
 * @param {number[]} arr
 * @return {number}
 */
var maxChunksToSorted = function (arr) {
  const st = []; // max of each chunk, non-decreasing
  for (const x of arr) {
    let curMax = x;
    while (st.length && st[st.length - 1] > x) curMax = Math.max(curMax, st.pop());
    st.push(curMax);
  }
  return st.length;
};
