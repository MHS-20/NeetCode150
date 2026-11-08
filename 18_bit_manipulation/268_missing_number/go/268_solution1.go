package bitmanipulation

func missingNumber(nums []int) int {
	res := len(nums)
	for i, n := range nums {
		res ^= i ^ n
	}
	return res
}
