import java.util.ArrayDeque;
import java.util.Deque;

class MinStack {
    // {value, minimum of everything up to and including it}
    private final Deque<int[]> st = new ArrayDeque<>();

    public MinStack() {}

    public void push(int value) {
        int curMin = st.isEmpty() ? value : Math.min(st.peek()[1], value);
        st.push(new int[] {value, curMin});
    }

    public void pop() {
        st.pop();
    }

    public int top() {
        return st.peek()[0];
    }

    public int getMin() {
        return st.peek()[1];
    }
}
