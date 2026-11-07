class Solution {
    public int minEatingSpeed(int[] piles, int h) {
        int maxPile = 0;
        for (int p : piles)
            maxPile = Math.max(maxPile, p);

        int left = 1, right = maxPile;
        while (left < right) {
            int k = left + (right - left) / 2;
            int hours = 0;
            for (int p : piles)
                hours += (p + k - 1) / k;

            if (hours > h)
                left = k + 1;
            else
                right = k;
        }
        return left;
    }
}
