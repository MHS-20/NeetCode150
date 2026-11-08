package bitmanipulation

func getSum(a int, b int) int {
	// Go's int is 64-bit: work in uint32 so the carry dies after bit 31
	sum, carry := uint32(a)^uint32(b), (uint32(a)&uint32(b))<<1

	for carry != 0 {
		tmp := (sum & carry) << 1
		sum ^= carry
		carry = tmp
	}

	return int(int32(sum))
}
