import java.util.ArrayDeque;
import java.util.Deque;

class MinStack {
    private final Deque<Integer> v = new ArrayDeque<>();
    private final Deque<Integer> mins = new ArrayDeque<>();

    public MinStack() {}

    public void push(int value) {
        v.push(value);

        int curMin = mins.isEmpty() ? value : Math.min(mins.peek(), value);
        mins.push(curMin);
    }

    public void pop() {
        v.pop();
        mins.pop();
    }

    public int top() {
        return v.peek();
    }

    public int getMin() {
        return mins.peek();
    }
}
