class MedianFinder {
    private final int[] cnt = new int[101];
    private int below = 0; // numbers < 0
    private int above = 0; // numbers > 100
    private int total = 0;

    private int kth(int k) {
        int seen = below; // outliers below the range come first in sorted order
        for (int v = 0; v <= 100; v++) {
            seen += cnt[v];
            if (seen >= k)
                return v;
        }
        return -1;
    }

    public void addNum(int num) {
        if (num < 0)
            below++;
        else if (num > 100)
            above++;
        else
            cnt[num]++;
        total++;
    }

    public double findMedian() {
        int a = kth((total + 1) / 2);
        int b = kth(total / 2 + 1);
        return (a + b) / 2.0;
    }
}
