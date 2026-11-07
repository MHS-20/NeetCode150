package greedy

func canCompleteCircuit(gas []int, cost []int) int {
	sumGas, sumCost := 0, 0
	for i := range gas {
		sumGas += gas[i]
		sumCost += cost[i]
	}

	if sumCost > sumGas {
		return -1
	}

	start, curGas, curPos := 0, 0, 0
	for {
		curGas += gas[curPos] - cost[curPos]

		curPos = (curPos + 1) % len(gas)

		if curPos == start {
			return start
		}

		if curGas < 0 {
			start = curPos
			curGas = 0
		}
	}
}
