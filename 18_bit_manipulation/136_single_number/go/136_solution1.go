package bitmanipulation

func singleNumber(nums []int) int {
	xr := 0
	for _, n := range nums {
		xr = xr ^ n
	}
	return xr
}
