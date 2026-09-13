import java.util.Arrays;

class Solution {
    public boolean isValidSudoku(char[][] board) {
        boolean[] seen = new boolean[9];

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.')
                    continue;
                int current = board[i][j] - '0' - 1;
                if (seen[current])
                    return false;
                seen[current] = true;
            }
            Arrays.fill(seen, false);
        }

        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                if (board[i][j] == '.')
                    continue;
                int current = board[i][j] - '0' - 1;
                if (seen[current])
                    return false;
                seen[current] = true;
            }
            Arrays.fill(seen, false);
        }

        for (int rowOffset = 0; rowOffset < 9; rowOffset += 3) {
            for (int colOffset = 0; colOffset < 9; colOffset += 3) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (board[i + rowOffset][j + colOffset] == '.')
                            continue;
                        int current = board[i + rowOffset][j + colOffset] - '0' - 1;
                        if (seen[current])
                            return false;
                        seen[current] = true;
                    }
                }
                Arrays.fill(seen, false);
            }
        }

        return true;
    }
}
