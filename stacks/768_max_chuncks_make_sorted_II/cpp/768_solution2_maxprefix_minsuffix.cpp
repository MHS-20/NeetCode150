#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

class Solution {
public:
  int maxChunksToSorted(vector<int> &arr) {
    int n = arr.size();
    vector<int> sufMin(n + 1, INT_MAX);
    for (int i = n - 1; i >= 0; --i)
      sufMin[i] = min(sufMin[i + 1], arr[i]);

    int chunks = 0, prefMax = INT_MIN;
    for (int i = 0; i < n; ++i) {
      prefMax = max(prefMax, arr[i]);
      if (prefMax <= sufMin[i + 1])
        ++chunks; // valid cut after i (i = n-1 always counts)
    }
    return chunks;
  }
};
