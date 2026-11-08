package bitmanipulation

func reverseBits(num uint32) uint32 {
	var res uint32
	for i := 0; i < 32; i++ {
		bit := (num >> i) & 1
		res = (res << 1) | bit
	}
	return res
}
