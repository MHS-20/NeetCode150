// Swap the two 16-bit halves.
// Within each half, swap the 8-bit halves.
// Then swap 4-bit groups, then 2-bit groups, then single bits
/**
 * @param {number} n - a positive integer
 * @return {number} - a positive integer
 */
var reverseBits = function (n) {
  let x = n;
  x = (x >>> 16) | (x << 16);
  x = ((x & 0xff00ff00) >>> 8) | ((x & 0x00ff00ff) << 8);
  x = ((x & 0xf0f0f0f0) >>> 4) | ((x & 0x0f0f0f0f) << 4);
  x = ((x & 0xcccccccc) >>> 2) | ((x & 0x33333333) << 2);
  x = ((x & 0xaaaaaaaa) >>> 1) | ((x & 0x55555555) << 1);
  return x >>> 0; // bitwise ops yield int32, convert back to unsigned
};
