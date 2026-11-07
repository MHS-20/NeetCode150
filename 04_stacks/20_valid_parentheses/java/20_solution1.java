import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public boolean isValid(String s) {
        Deque<Character> expected = new ArrayDeque<>(); // closing brackets we still owe

        for (char c : s.toCharArray()) {
            switch (c) {
                case '(':
                    expected.push(')');
                    break;
                case '[':
                    expected.push(']');
                    break;
                case '{':
                    expected.push('}');
                    break;
                default:
                    if (expected.isEmpty() || expected.pop() != c)
                        return false;
            }
        }
        return expected.isEmpty();
    }
}
