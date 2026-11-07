import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public boolean checkValidString(String s) {
        Deque<Integer> open = new ArrayDeque<>(), star = new ArrayDeque<>(); // indices of unmatched '(' and '*'

        for (int i = 0; i < s.length(); i++) {
            switch (s.charAt(i)) {
                case '(' -> open.push(i);
                case '*' -> star.push(i);
                case ')' -> {
                    if (!open.isEmpty())
                        open.pop();
                    else if (!star.isEmpty())
                        star.pop();
                    else
                        return false;
                }
            }
        }

        // each leftover '(' needs a later '*' to close it
        while (!open.isEmpty()) {
            if (star.isEmpty() || star.peek() < open.peek())
                return false;
            open.pop();
            star.pop();
        }
        return true;
    }
}
