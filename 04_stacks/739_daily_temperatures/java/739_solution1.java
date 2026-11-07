import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int[] dailyTemperatures(int[] temps) {
        int[] res = new int[temps.length];
        Deque<Integer> st = new ArrayDeque<>(); // indices with no warmer day yet

        for (int i = 0; i < temps.length; i++) {
            while (!st.isEmpty() && temps[i] > temps[st.peek()]) {
                int j = st.pop();
                res[j] = i - j;
            }
            st.push(i);
        }
        return res;
    }
}
