int minEatingSpeed(int *piles, int pilesSize, int h) {
    int maxPile = 0;
    for (int i = 0; i < pilesSize; i++)
        if (piles[i] > maxPile)
            maxPile = piles[i];

    int left = 1, right = maxPile;
    while (left < right) {
        int k = left + (right - left) / 2;
        int hours = 0;
        for (int i = 0; i < pilesSize; i++)
            hours += (piles[i] + k - 1) / k;

        if (hours > h)
            left = k + 1;
        else
            right = k;
    }
    return left;
}
