class Solution {
    public boolean isValidSudoku(char[][] board) {
        int[] seenRows = new int[9];
        int[] seenCols = new int[9];
        int[] seenBoxes = new int[9];

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.')
                    continue;

                int current = board[i][j] - '0' - 1;
                int box = (i / 3) * 3 + (j / 3);

                if (!checkAndMark(seenRows, i, current))
                    return false;
                if (!checkAndMark(seenCols, j, current))
                    return false;
                if (!checkAndMark(seenBoxes, box, current))
                    return false;
            }
        }

        return true;
    }

    private boolean checkAndMark(int[] masks, int idx, int bit) {
        if ((masks[idx] & (1 << bit)) != 0)
            return false;
        masks[idx] |= (1 << bit);
        return true;
    }
}
