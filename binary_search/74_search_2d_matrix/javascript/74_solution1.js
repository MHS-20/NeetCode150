class Solution {
  searchMatrix(matrix, target) {
    const rows = matrix.length, cols = matrix[0].length;
    let left = 0, right = rows * cols - 1;

    while (left <= right) {
      const mid = left + Math.floor((right - left) / 2);
      const i = Math.floor(mid / cols), j = mid % cols;

      if (matrix[i][j] === target) return true;
      if (matrix[i][j] > target) right = mid - 1;
      else left = mid + 1;
    }
    return false;
  }
}
