class Solution {
    private static final int[][] DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    private int rows, cols;

    public void solve(char[][] board) {
        rows = board.length;
        cols = board[0].length;

        // 1. mark border-connected 'O's as safe
        for (int i = 0; i < rows; i++) {
            dfs(board, i, 0);
            dfs(board, i, cols - 1);
        }
        for (int j = 0; j < cols; j++) {
            dfs(board, 0, j);
            dfs(board, rows - 1, j);
        }

        // 2. capture leftover 'O's, restore safe ones
        for (char[] row : board)
            for (int j = 0; j < cols; j++) {
                if (row[j] == 'O')
                    row[j] = 'X';
                else if (row[j] == '.')
                    row[j] = 'O';
            }
    }

    private void dfs(char[][] board, int r, int c) {
        if (r < 0 || c < 0 || r >= rows || c >= cols || board[r][c] != 'O')
            return;
        board[r][c] = '.';
        for (int[] d : DIRS)
            dfs(board, r + d[0], c + d[1]);
    }
}
