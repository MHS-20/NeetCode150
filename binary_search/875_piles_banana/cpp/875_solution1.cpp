class Solution {
public:
  int minEatingSpeed(vector<int> &piles, int h) {
    int maxpile = *max_element(piles.begin(), piles.end());
    int k = maxpile / 2, sum = 0;
    int left = 1, right = maxpile;

    while (left < right) {
      sum = 0;
      k = (left + right) / 2;
      for (int n : piles)
        sum += (n + k - 1) / k;

      if (sum > h)
        left = k + 1;
      else
        right = k;
    }

    return left;
  }
};
