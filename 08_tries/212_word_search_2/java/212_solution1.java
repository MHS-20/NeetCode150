import java.util.ArrayList;
import java.util.List;

class Solution {
    private static class Node {
        Node[] children = new Node[26];
        String word; // non-null means a word ends here
    }

    private static final int[][] DIRS = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    private void insert(Node root, String word) {
        Node cur = root;
        for (char ch : word.toCharArray()) {
            int i = ch - 'a';
            if (cur.children[i] == null)
                cur.children[i] = new Node();
            cur = cur.children[i];
        }
        cur.word = word;
    }

    private void dfs(char[][] board, Node node, int r, int c, List<String> res) {
        char ch = board[r][c];
        Node next = node.children[ch - 'a'];
        if (next == null)
            return;

        if (next.word != null) {
            res.add(next.word);
            next.word = null; // avoid duplicates
        }

        board[r][c] = '#'; // mark visited
        for (int[] d : DIRS) {
            int nr = r + d[0], nc = c + d[1];
            if (nr < 0 || nr >= board.length || nc < 0 || nc >= board[0].length)
                continue;
            if (board[nr][nc] == '#')
                continue;
            dfs(board, next, nr, nc, res);
        }
        board[r][c] = ch; // unmark
    }

    public List<String> findWords(char[][] board, String[] words) {
        Node root = new Node();
        for (String w : words)
            insert(root, w);

        List<String> res = new ArrayList<>();
        for (int r = 0; r < board.length; r++)
            for (int c = 0; c < board[0].length; c++)
                dfs(board, root, r, c, res);
        return res;
    }
}
