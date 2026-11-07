#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int maxChunksToSorted(vector<int> &arr) {
    int n = arr.size();
    vector<int> prefixMax(n), suffixMin(n);

    prefixMax[0] = arr[0];
    for (int i = 1; i < n; ++i)
      prefixMax[i] = max(prefixMax[i - 1], arr[i]);

    suffixMin[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; --i)
      suffixMin[i] = min(suffixMin[i + 1], arr[i]);

    int chunks = 1; // the last chunk always exists
    for (int i = 0; i < n - 1; ++i)
      if (prefixMax[i] <= suffixMin[i + 1])
        ++chunks;

    return chunks;
  }
};
