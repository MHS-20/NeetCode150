// Swap the two 16-bit halves.
// Within each half, swap the 8-bit halves.
// Then swap 4-bit groups, then 2-bit groups, then single bits
package bitmanipulation

func reverseBits(num uint32) uint32 {
	x := num
	x = (x >> 16) | (x << 16)
	x = ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8)
	x = ((x & 0xF0F0F0F0) >> 4) | ((x & 0x0F0F0F0F) << 4)
	x = ((x & 0xCCCCCCCC) >> 2) | ((x & 0x33333333) << 2)
	x = ((x & 0xAAAAAAAA) >> 1) | ((x & 0x55555555) << 1)
	return x
}
