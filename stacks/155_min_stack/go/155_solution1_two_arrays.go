package main

type MinStack struct {
	v    []int
	mins []int
}

func Constructor() MinStack {
	return MinStack{}
}

func (s *MinStack) Push(value int) {
	s.v = append(s.v, value)

	curMin := value
	if n := len(s.mins); n > 0 && s.mins[n-1] < value {
		curMin = s.mins[n-1]
	}
	s.mins = append(s.mins, curMin)
}

func (s *MinStack) Pop() {
	s.v = s.v[:len(s.v)-1]
	s.mins = s.mins[:len(s.mins)-1]
}

func (s *MinStack) Top() int {
	return s.v[len(s.v)-1]
}

func (s *MinStack) GetMin() int {
	return s.mins[len(s.mins)-1]
}
