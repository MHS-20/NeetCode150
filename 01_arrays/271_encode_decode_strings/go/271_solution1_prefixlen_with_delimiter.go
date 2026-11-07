package main

import (
	"strconv"
	"strings"
)

func encode(strs []string) string {
	var encoded strings.Builder
	for _, s := range strs {
		encoded.WriteString(strconv.Itoa(len(s)))
		encoded.WriteByte('-')
		encoded.WriteString(s)
	}
	return encoded.String()
}

func decode(s string) []string {
	res := []string{}
	i := 0

	for i < len(s) {
		delimPos := strings.IndexByte(s[i:], '-') + i
		length, _ := strconv.Atoi(s[i:delimPos])

		res = append(res, s[delimPos+1:delimPos+1+length])
		i = delimPos + 1 + length
	}

	return res
}
