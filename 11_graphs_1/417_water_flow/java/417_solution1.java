import java.util.ArrayList;
import java.util.List;

class Solution {
    private static final int[][] DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    private int rows, cols;

    public List<List<Integer>> pacificAtlantic(int[][] heights) {
        rows = heights.length;
        cols = heights[0].length;
        boolean[][] pacific = new boolean[rows][cols];
        boolean[][] atlantic = new boolean[rows][cols];

        for (int i = 0; i < rows; i++) {
            dfs(heights, pacific, i, 0, Integer.MIN_VALUE);
            dfs(heights, atlantic, i, cols - 1, Integer.MIN_VALUE);
        }
        for (int j = 0; j < cols; j++) {
            dfs(heights, pacific, 0, j, Integer.MIN_VALUE);
            dfs(heights, atlantic, rows - 1, j, Integer.MIN_VALUE);
        }

        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (pacific[i][j] && atlantic[i][j])
                    result.add(List.of(i, j));
        return result;
    }

    private void dfs(int[][] heights, boolean[][] ocean, int r, int c, int prevHeight) {
        if (r < 0 || c < 0 || r >= rows || c >= cols)
            return;
        if (ocean[r][c] || heights[r][c] < prevHeight)
            return;

        ocean[r][c] = true;
        for (int[] d : DIRS)
            dfs(heights, ocean, r + d[0], c + d[1], heights[r][c]);
    }
}
