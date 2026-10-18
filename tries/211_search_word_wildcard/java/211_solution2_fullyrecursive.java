class WordDictionary {
    private static class Node {
        Node[] children = new Node[26];
        boolean isEnd;
    }

    private final Node root = new Node();

    public void addWord(String word) {
        Node cur = root;
        for (char ch : word.toCharArray()) {
            int i = ch - 'a';
            if (cur.children[i] == null)
                cur.children[i] = new Node();
            cur = cur.children[i];
        }
        cur.isEnd = true;
    }

    public boolean search(String word) {
        return dfs(root, word, 0);
    }

    private boolean dfs(Node cur, String word, int i) {
        if (cur == null)
            return false;
        if (i == word.length())
            return cur.isEnd;

        char ch = word.charAt(i);
        if (ch != '.')
            return dfs(cur.children[ch - 'a'], word, i + 1);

        for (Node child : cur.children)
            if (dfs(child, word, i + 1))
                return true;
        return false;
    }
}
