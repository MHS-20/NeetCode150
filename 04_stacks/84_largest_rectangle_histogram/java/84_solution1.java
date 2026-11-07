import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int largestRectangleArea(int[] heights) {
        int n = heights.length, best = 0;
        Deque<Integer> st = new ArrayDeque<>(); // indices of increasing heights

        for (int i = 0; i <= n; i++) {
            int h = i < n ? heights[i] : 0; // sentinel flushes the stack
            while (!st.isEmpty() && heights[st.peek()] > h) {
                int height = heights[st.pop()];
                int prev = st.isEmpty() ? -1 : st.peek();
                best = Math.max(best, height * (i - prev - 1));
            }
            st.push(i);
        }
        return best;
    }
}
