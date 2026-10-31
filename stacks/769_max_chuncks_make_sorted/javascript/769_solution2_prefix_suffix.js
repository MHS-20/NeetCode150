/**
 * @param {number[]} arr
 * @return {number}
 */
var maxChunksToSorted = function (arr) {
  const n = arr.length;
  const prefixMax = new Array(n);
  const suffixMin = new Array(n);

  prefixMax[0] = arr[0];
  for (let i = 1; i < n; i++) prefixMax[i] = Math.max(prefixMax[i - 1], arr[i]);

  suffixMin[n - 1] = arr[n - 1];
  for (let i = n - 2; i >= 0; i--) suffixMin[i] = Math.min(suffixMin[i + 1], arr[i]);

  let chunks = 1; // the last chunk always exists
  for (let i = 0; i < n - 1; i++) if (prefixMax[i] <= suffixMin[i + 1]) chunks++;

  return chunks;
};
