import java.util.ArrayList;
import java.util.List;

class Solution {
    private static final String[] MAPPING = {"", "", "abc", "def", "ghi",
                                             "jkl", "mno", "pqrs", "tuv", "wxyz"};

    public List<String> letterCombinations(String digits) {
        List<String> result = new ArrayList<>();
        if (digits.isEmpty()) {
            return result;
        }
        backtrack(digits, 0, new StringBuilder(), result);
        return result;
    }

    private void backtrack(String digits, int idx, StringBuilder cur, List<String> result) {
        if (idx == digits.length()) {
            result.add(cur.toString());
            return;
        }
        for (char ch : MAPPING[digits.charAt(idx) - '0'].toCharArray()) {
            cur.append(ch); // choose
            backtrack(digits, idx + 1, cur, result);
            cur.deleteCharAt(cur.length() - 1); // un-choose
        }
    }
}
