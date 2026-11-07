class Solution {
  generateParenthesis(n) {
    const res = [];

    const build = (opened, closed, cur) => {
      if (closed === n) {
        // implies opened === n too
        res.push(cur);
        return;
      }
      if (opened < n) build(opened + 1, closed, cur + "(");
      if (closed < opened) build(opened, closed + 1, cur + ")");
    };

    build(0, 0, "");
    return res;
  }
}
