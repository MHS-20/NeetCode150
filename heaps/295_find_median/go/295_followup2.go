package heaps

type MedianFinder struct {
	cnt   [101]int
	below int // numbers < 0
	above int // numbers > 100
	total int
}

func Constructor() MedianFinder {
	return MedianFinder{}
}

func (this *MedianFinder) kth(k int) int {
	seen := this.below // outliers below the range come first in sorted order
	for v := 0; v <= 100; v++ {
		seen += this.cnt[v]
		if seen >= k {
			return v
		}
	}
	return -1
}

func (this *MedianFinder) AddNum(num int) {
	switch {
	case num < 0:
		this.below++
	case num > 100:
		this.above++
	default:
		this.cnt[num]++
	}
	this.total++
}

func (this *MedianFinder) FindMedian() float64 {
	a := this.kth((this.total + 1) / 2)
	b := this.kth(this.total/2 + 1)
	return float64(a+b) / 2
}
