import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int evalRPN(String[] tokens) {
        Deque<Integer> st = new ArrayDeque<>();

        for (String s : tokens) {
            if (s.equals("+") || s.equals("-") || s.equals("*") || s.equals("/")) {
                int b = st.pop();
                int a = st.pop();

                if (s.equals("+"))
                    st.push(a + b);
                else if (s.equals("-"))
                    st.push(a - b);
                else if (s.equals("*"))
                    st.push(a * b);
                else
                    st.push(a / b);
            } else {
                st.push(Integer.parseInt(s));
            }
        }

        return st.peek();
    }
}
