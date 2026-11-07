import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> res = new ArrayList<>();
        backtrack(n, 0, 0, new StringBuilder(2 * n), res);
        return res;
    }

    private void backtrack(int n, int opened, int closed, StringBuilder cur, List<String> res) {
        if (closed == n) { // implies opened == n too
            res.add(cur.toString()); // copies once, only for finished answers
            return;
        }

        if (opened < n) {
            cur.append('(');                            // choose
            backtrack(n, opened + 1, closed, cur, res); // explore
            cur.deleteCharAt(cur.length() - 1);         // undo
        }

        if (closed < opened) {
            cur.append(')');
            backtrack(n, opened, closed + 1, cur, res);
            cur.deleteCharAt(cur.length() - 1);
        }
    }
}
