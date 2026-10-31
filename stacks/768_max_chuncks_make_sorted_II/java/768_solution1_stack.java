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

// ---- Alternative Compact Version ----
// class Solution {
//     public int maxChunksToSorted(int[] arr) {
//         int[] st = new int[arr.length]; // max of each chunk, non-decreasing
//         int top = 0;
//         for (int x : arr) {
//             int curMax = x;
//             while (top > 0 && st[top - 1] > x)
//                 curMax = Math.max(curMax, st[--top]);
//             st[top++] = curMax;
//         }
//         return top;
//     }
// }
