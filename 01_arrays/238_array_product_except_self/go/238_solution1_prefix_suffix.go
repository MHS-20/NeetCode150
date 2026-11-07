package main

func productExceptSelf(nums []int) []int {
	n := len(nums)
	prefixes := make([]int, n)
	suffixes := make([]int, n)
	ans := make([]int, n)

	prefixes[0] = 1
	for i := 1; i < n; i++ {
		prefixes[i] = prefixes[i-1] * nums[i-1]
	}

	suffixes[n-1] = 1
	for i := n - 2; i >= 0; i-- {
		suffixes[i] = suffixes[i+1] * nums[i+1]
	}

	for i := 0; i < n; i++ {
		ans[i] = prefixes[i] * suffixes[i]
	}

	return ans
}
