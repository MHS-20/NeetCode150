import java.util.ArrayDeque;
import java.util.HashSet;
import java.util.List;
import java.util.Queue;
import java.util.Set;

class Solution {
    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        Set<String> words = new HashSet<>(wordList);
        if (!words.contains(endWord))
            return 0;

        Queue<String> q = new ArrayDeque<>();
        q.offer(beginWord);
        words.remove(beginWord);
        int length = 1;

        while (!q.isEmpty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                char[] w = q.poll().toCharArray();

                for (int pos = 0; pos < w.length; pos++) {
                    char original = w[pos];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original)
                            continue;
                        w[pos] = c;
                        String s = new String(w);
                        if (s.equals(endWord))
                            return length + 1;
                        if (words.remove(s))
                            q.offer(s);
                    }
                    w[pos] = original;
                }
            }
            length++;
        }
        return 0;
    }
}
