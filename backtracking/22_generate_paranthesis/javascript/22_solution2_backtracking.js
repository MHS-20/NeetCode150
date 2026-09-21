class Solution {
  generateParenthesis(n) {
    const res = [];
    const cur = [];

    const backtrack = (opened, closed) => {
      if (closed === n) {
        // implies opened === n too
        res.push(cur.join("")); // joins once, only for finished answers
        return;
      }

      if (opened < n) {
        cur.push("("); // choose
        backtrack(opened + 1, closed); // explore
        cur.pop(); // undo
      }

      if (closed < opened) {
        cur.push(")");
        backtrack(opened, closed + 1);
        cur.pop();
      }
    };

    backtrack(0, 0);
    return res;
  }
}
