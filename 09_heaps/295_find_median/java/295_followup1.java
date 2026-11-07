class MedianFinder {
    private final int[] cnt = new int[101];
    private int total = 0;

    private int kth(int k) { // k-th smallest, 1-indexed
        int seen = 0;
        for (int v = 0; v <= 100; v++) {
            seen += cnt[v];
            if (seen >= k)
                return v;
        }
        return -1; // unreachable if 1 <= k <= total
    }

    public void addNum(int num) {
        cnt[num]++;
        total++;
    }

    public double findMedian() {
        int a = kth((total + 1) / 2);
        int b = kth(total / 2 + 1);
        return (a + b) / 2.0;
    }
}
