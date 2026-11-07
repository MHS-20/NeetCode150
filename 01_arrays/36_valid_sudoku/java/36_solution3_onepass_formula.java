class Solution {
    public boolean isValidSudoku(char[][] board) {
        boolean[][] seenRows = new boolean[9][9];
        boolean[][] seenCols = new boolean[9][9];
        boolean[][] seenBoxes = new boolean[9][9];

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.')
                    continue;

                int current = board[i][j] - '0' - 1;
                int box = (i / 3) * 3 + (j / 3);

                if (!checkAndMark(seenRows[i], current))
                    return false;
                if (!checkAndMark(seenCols[j], current))
                    return false;
                if (!checkAndMark(seenBoxes[box], current))
                    return false;
            }
        }

        return true;
    }

    private boolean checkAndMark(boolean[] arr, int idx) {
        if (arr[idx])
            return false;
        arr[idx] = true;
        return true;
    }
}
