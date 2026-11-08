/**
 * @param {number[][]} matrix
 * @return {void} Do not return anything, modify matrix in-place instead.
 */
var setZeroes = function (matrix) {
  const m = matrix.length, n = matrix[0].length;
  const zeroRow = new Array(m).fill(false), zeroCol = new Array(n).fill(false);

  for (let i = 0; i < m; i++)
    for (let j = 0; j < n; j++)
      if (matrix[i][j] === 0) zeroRow[i] = zeroCol[j] = true;

  for (let i = 0; i < m; i++)
    for (let j = 0; j < n; j++)
      if (zeroRow[i] || zeroCol[j]) matrix[i][j] = 0;
};
