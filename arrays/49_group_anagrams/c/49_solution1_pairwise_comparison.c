#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool isAnagram(const char *s, const char *t) {
  int freq[26] = {0};
  int lenS = strlen(s), lenT = strlen(t);
  if (lenS != lenT)
    return false;

  for (int i = 0; i < lenS; i++)
    freq[s[i] - 'a']++;
  for (int i = 0; i < lenT; i++) {
    freq[t[i] - 'a']--;
    if (freq[t[i] - 'a'] < 0)
      return false;
  }
  return true;
}

char ***groupAnagrams(char **strs, int strsSize, int *returnSize,
                       int **returnColumnSizes) {
  int *groupIndex = (int *)malloc(strsSize * sizeof(int));
  int *groupHead = (int *)malloc(strsSize * sizeof(int));
  int *groupCounts = (int *)calloc(strsSize, sizeof(int));
  int groupTotal = 0;

  for (int i = 0; i < strsSize; i++) {
    int found = -1;
    for (int g = 0; g < groupTotal; g++) {
      if (isAnagram(strs[i], strs[groupHead[g]])) {
        found = g;
        break;
      }
    }

    if (found == -1) {
      found = groupTotal;
      groupHead[groupTotal] = i;
      groupTotal++;
    }

    groupIndex[i] = found;
    groupCounts[found]++;
  }

  char ***result = (char ***)malloc(groupTotal * sizeof(char **));
  *returnColumnSizes = (int *)malloc(groupTotal * sizeof(int));
  int *filled = (int *)calloc(groupTotal, sizeof(int));

  for (int g = 0; g < groupTotal; g++) {
    result[g] = (char **)malloc(groupCounts[g] * sizeof(char *));
    (*returnColumnSizes)[g] = groupCounts[g];
  }

  for (int i = 0; i < strsSize; i++) {
    int g = groupIndex[i];
    result[g][filled[g]++] = strs[i];
  }

  free(groupIndex);
  free(groupHead);
  free(groupCounts);
  free(filled);

  *returnSize = groupTotal;
  return result;
}
