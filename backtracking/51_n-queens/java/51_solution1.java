import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    private boolean[] cols, diag1, diag2;

    public List<List<String>> solveNQueens(int n) {
        List<List<String>> result = new ArrayList<>();
        char[][] board = new char[n][n];
        for (char[] row : board) {
            Arrays.fill(row, '.');
        }
        cols = new boolean[n];
        diag1 = new boolean[2 * n - 1];
        diag2 = new boolean[2 * n - 1];
        backtrack(n, 0, board, result);
        return result;
    }

    private void backtrack(int n, int row, char[][] board, List<List<String>> result) {
        if (row == n) {
            List<String> snapshot = new ArrayList<>(n);
            for (char[] r : board) {
                snapshot.add(new String(r));
            }
            result.add(snapshot);
            return;
        }

        for (int col = 0; col < n; col++) {
            int d1 = row + col;         // "/" diagonal
            int d2 = row - col + n - 1; // "\" diagonal, shifted
            if (cols[col] || diag1[d1] || diag2[d2]) {
                continue;
            }

            board[row][col] = 'Q';
            cols[col] = diag1[d1] = diag2[d2] = true;

            backtrack(n, row + 1, board, result);

            board[row][col] = '.';
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
    }
}
