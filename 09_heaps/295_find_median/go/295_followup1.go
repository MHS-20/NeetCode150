package heaps

type MedianFinder struct {
	cnt   [101]int
	total int
}

func Constructor() MedianFinder {
	return MedianFinder{}
}

func (this *MedianFinder) kth(k int) int { // k-th smallest, 1-indexed
	seen := 0
	for v := 0; v <= 100; v++ {
		seen += this.cnt[v]
		if seen >= k {
			return v
		}
	}
	return -1 // unreachable if 1 <= k <= total
}

func (this *MedianFinder) AddNum(num int) {
	this.cnt[num]++
	this.total++
}

func (this *MedianFinder) FindMedian() float64 {
	a := this.kth((this.total + 1) / 2)
	b := this.kth(this.total/2 + 1)
	return float64(a+b) / 2
}
