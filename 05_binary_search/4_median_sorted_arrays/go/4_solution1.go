package main

import "math"

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	// Always binary search on the smaller array
	if len(nums1) > len(nums2) {
		return findMedianSortedArrays(nums2, nums1)
	}

	n, m := len(nums1), len(nums2)
	left, right := 0, n // number of elements taken from nums1 into left half
	total := n + m
	halfLeft := (total + 1) / 2 // size of left half (handles odd/even uniformly)

	for left <= right {
		i := left + (right-left)/2 // elements taken from nums1
		j := halfLeft - i          // elements taken from nums2

		// Sentinels for out-of-range boundaries
		nums1Left := math.MinInt32
		if i != 0 {
			nums1Left = nums1[i-1]
		}
		nums1Right := math.MaxInt32
		if i != n {
			nums1Right = nums1[i]
		}
		nums2Left := math.MinInt32
		if j != 0 {
			nums2Left = nums2[j-1]
		}
		nums2Right := math.MaxInt32
		if j != m {
			nums2Right = nums2[j]
		}

		if nums1Left <= nums2Right && nums2Left <= nums1Right {
			// Valid partition found
			if total%2 == 1 {
				return float64(max(nums1Left, nums2Left))
			}
			a := max(nums1Left, nums2Left)
			b := min(nums1Right, nums2Right)
			return float64(a+b) / 2.0
		} else if nums1Left > nums2Right {
			right = i - 1 // too many from nums1, shrink
		} else {
			left = i + 1 // too few from nums1, grow
		}
	}

	return 0.0 // unreachable if inputs are valid sorted arrays
}
