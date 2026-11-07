class Solution {
    private static final int[][] DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    public boolean exist(char[][] board, String word) {
        for (int r = 0; r < board.length; r++) {
            for (int c = 0; c < board[0].length; c++) {
                if (dfs(board, word, 0, r, c)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean dfs(char[][] board, String word, int idx, int row, int col) {
        char ch = word.charAt(idx);
        if (ch != board[row][col]) {
            return false;
        }

        if (idx == word.length() - 1) {
            return true;
        }

        board[row][col] = '#';
        for (int[] d : DIRS) {
            int nr = row + d[0], nc = col + d[1];

            if (nr < 0 || nr >= board.length || nc < 0 || nc >= board[0].length) {
                continue;
            }

            if (dfs(board, word, idx + 1, nr, nc)) {
                return true;
            }
        }

        board[row][col] = ch;
        return false;
    }
}
