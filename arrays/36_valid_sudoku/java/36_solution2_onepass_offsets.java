import java.util.Arrays;

class Solution {
    public boolean isValidSudoku(char[][] board) {
        boolean[] seenGrid = new boolean[9];
        boolean[][] seenCol = new boolean[9][9];
        boolean[][] seenRow = new boolean[9][9];

        for (int rowOffset = 0; rowOffset < 9; rowOffset += 3) {
            for (int colOffset = 0; colOffset < 9; colOffset += 3) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (board[i + rowOffset][j + colOffset] == '.')
                            continue;

                        int current = board[i + rowOffset][j + colOffset] - '0' - 1;

                        if (seenGrid[current])
                            return false;
                        seenGrid[current] = true;

                        if (seenRow[i + rowOffset][current])
                            return false;
                        seenRow[i + rowOffset][current] = true;

                        if (seenCol[j + colOffset][current])
                            return false;
                        seenCol[j + colOffset][current] = true;
                    }
                }
                Arrays.fill(seenGrid, false);
            }
        }

        return true;
    }
}
