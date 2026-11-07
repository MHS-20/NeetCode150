package main

import (
	"strconv"
	"strings"
)

func groupAnagrams(strs []string) [][]string {
	groups := make(map[string][]string)

	for _, s := range strs {
		key := serializeFrequency(s)
		groups[key] = append(groups[key], s)
	}

	result := make([][]string, 0, len(groups))
	for _, group := range groups {
		result = append(result, group)
	}
	return result
}

func serializeFrequency(s string) string {
	var alphabet [26]int
	for _, c := range s {
		alphabet[c-'a']++
	}

	var key strings.Builder
	for i := 0; i < 26; i++ {
		key.WriteString(strconv.Itoa(alphabet[i]))
		key.WriteByte('#')
	}
	return key.String()
}
