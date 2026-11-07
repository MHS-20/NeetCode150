#include <limits.h>

int maxProfit(int *prices, int pricesSize) {
    int mn = INT_MAX;
    int profit = 0;

    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < mn) {
            mn = prices[i];
        }

        if (prices[i] - mn > profit) {
            profit = prices[i] - mn;
        }
    }

    return profit;
}
