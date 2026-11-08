class Solution {
    public void setZeroes(int[][] matrix) {
        int m = matrix.length, n = matrix[0].length;
        boolean[] zeroRow = new boolean[m], zeroCol = new boolean[n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (matrix[i][j] == 0)
                    zeroRow[i] = zeroCol[j] = true;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (zeroRow[i] || zeroCol[j])
                    matrix[i][j] = 0;
    }
}
