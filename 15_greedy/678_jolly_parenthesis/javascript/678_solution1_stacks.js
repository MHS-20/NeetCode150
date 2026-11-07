/**
 * @param {string} s
 * @return {boolean}
 */
var checkValidString = function (s) {
  const open = [], star = []; // indices of unmatched '(' and '*'

  for (let i = 0; i < s.length; i++) {
    switch (s[i]) {
      case "(":
        open.push(i);
        break;
      case "*":
        star.push(i);
        break;
      case ")":
        if (open.length) open.pop();
        else if (star.length) star.pop();
        else return false;
        break;
    }
  }

  // each leftover '(' needs a later '*' to close it
  while (open.length) {
    if (!star.length || star[star.length - 1] < open[open.length - 1]) return false;
    open.pop();
    star.pop();
  }
  return true;
};
