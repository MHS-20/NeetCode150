/**
 * @param {number[]} nums
 * @return {number}
 */
var singleNumber = function (nums) {
  let xr = 0;
  for (const n of nums) xr = xr ^ n;
  return xr;
};
