package main

import "strconv"

func evalRPN(tokens []string) int {
	st := []int{}

	for _, s := range tokens {
		if s == "+" || s == "-" || s == "*" || s == "/" {
			n := len(st)
			a, b := st[n-2], st[n-1]
			st = st[:n-2]

			switch s {
			case "+":
				st = append(st, a+b)
			case "-":
				st = append(st, a-b)
			case "*":
				st = append(st, a*b)
			default:
				st = append(st, a/b)
			}
		} else {
			v, _ := strconv.Atoi(s)
			st = append(st, v)
		}
	}

	return st[len(st)-1]
}
