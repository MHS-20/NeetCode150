import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int maxChunksToSorted(int[] arr) {
        Deque<Integer> st = new ArrayDeque<>();

        for (int n : arr) {
            if (st.isEmpty() || n > st.peek()) {
                st.push(n);
            } else {
                int mx = st.pop();
                while (!st.isEmpty() && n <= st.peek())
                    st.pop();
                st.push(mx);
            }
        }

        return st.size();
    }
}
