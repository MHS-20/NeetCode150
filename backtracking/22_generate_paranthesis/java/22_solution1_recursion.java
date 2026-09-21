import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> res = new ArrayList<>();
        build(n, 0, 0, "", res);
        return res;
    }

    private void build(int n, int opened, int closed, String cur, List<String> res) {
        if (closed == n) { // implies opened == n too
            res.add(cur);
            return;
        }
        if (opened < n)
            build(n, opened + 1, closed, cur + '(', res);
        if (closed < opened)
            build(n, opened, closed + 1, cur + ')', res);
    }
}
