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
        return searchFrom(root, word, 0);
    }

    private boolean searchFrom(Node cur, String word, int pos) {
        for (int i = pos; i < word.length(); i++) {
            char ch = word.charAt(i);
            if (ch != '.') {
                cur = cur.children[ch - 'a'];
                if (cur == null)
                    return false;
            } else {
                for (Node n : cur.children) {
                    if (n != null && searchFrom(n, word, i + 1))
                        return true;
                }
                return false;
            }
        }
        return cur.isEnd;
    }
}
