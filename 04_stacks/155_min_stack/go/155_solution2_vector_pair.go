package main

type entry struct {
	value    int
	minSoFar int // minimum of everything up to and including value
}

type MinStack struct {
	st []entry
}

func Constructor() MinStack {
	return MinStack{}
}

func (s *MinStack) Push(value int) {
	curMin := value
	if n := len(s.st); n > 0 && s.st[n-1].minSoFar < value {
		curMin = s.st[n-1].minSoFar
	}
	s.st = append(s.st, entry{value, curMin})
}

func (s *MinStack) Pop() {
	s.st = s.st[:len(s.st)-1]
}

func (s *MinStack) Top() int {
	return s.st[len(s.st)-1].value
}

func (s *MinStack) GetMin() int {
	return s.st[len(s.st)-1].minSoFar
}
