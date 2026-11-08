var DetectSquares = function () {
  this.cnt = new Map(); // "x,y" -> count
};

DetectSquares.prototype.get = function (x, y) {
  return this.cnt.get(`${x},${y}`) ?? 0;
};

/**
 * @param {number[]} point
 * @return {void}
 */
DetectSquares.prototype.add = function (point) {
  const k = `${point[0]},${point[1]}`;
  this.cnt.set(k, (this.cnt.get(k) ?? 0) + 1);
};

/**
 * @param {number[]} point
 * @return {number}
 */
DetectSquares.prototype.count = function (point) {
  const [x, y] = point;
  let res = 0;

  for (const [k, c] of this.cnt) {
    const [px, py] = k.split(",").map(Number);
    if (px === x || Math.abs(px - x) !== Math.abs(py - y))
      continue; // must be a diagonal corner with side length > 0
    res += c * this.get(x, py) * this.get(px, y);
  }
  return res;
};
