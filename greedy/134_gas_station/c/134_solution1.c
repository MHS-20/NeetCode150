int canCompleteCircuit(int *gas, int gasSize, int *cost, int costSize) {
  (void)costSize;
  int sumGas = 0, sumCost = 0;
  for (int i = 0; i < gasSize; i++) {
    sumGas += gas[i];
    sumCost += cost[i];
  }

  if (sumCost > sumGas)
    return -1;

  int start = 0, curGas = 0, curPos = 0;
  for (;;) {
    curGas += gas[curPos] - cost[curPos];

    curPos = (curPos + 1) % gasSize;

    if (curPos == start)
      return start;

    if (curGas < 0) {
      start = curPos;
      curGas = 0;
    }
  }
}
