package main

import "unicode"

func isPalindrome(s string) bool {
	runes := []rune(s)
	left, right := 0, len(runes)-1

	for left < right {
		for left < right && !unicode.IsLetter(runes[left]) && !unicode.IsDigit(runes[left]) {
			left++
		}
		for left < right && !unicode.IsLetter(runes[right]) && !unicode.IsDigit(runes[right]) {
			right--
		}

		if unicode.ToLower(runes[left]) != unicode.ToLower(runes[right]) {
			return false
		}

		left++
		right--
	}

	return true
}
