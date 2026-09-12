#include <stdlib.h>
#include <string.h>

static int cmpChar(const void *a, const void *b) {
  return (*(char *)a - *(char *)b);
}

char ***groupAnagrams(char **strs, int strsSize, int *returnSize,
                       int **returnColumnSizes) {
  char **keys = (char **)malloc(strsSize * sizeof(char *));
  int *groupIndex = (int *)malloc(strsSize * sizeof(int));
  char **groupKeys = (char **)malloc(strsSize * sizeof(char *));
  int *groupCounts = (int *)calloc(strsSize, sizeof(int));
  int groupTotal = 0;

  for (int i = 0; i < strsSize; i++) {
    int len = strlen(strs[i]);
    keys[i] = (char *)malloc((len + 1) * sizeof(char));
    strcpy(keys[i], strs[i]);
    qsort(keys[i], len, sizeof(char), cmpChar);

    int found = -1;
    for (int g = 0; g < groupTotal; g++) {
      if (strcmp(keys[i], groupKeys[g]) == 0) {
        found = g;
        break;
      }
    }

    if (found == -1) {
      found = groupTotal;
      groupKeys[groupTotal] = keys[i];
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

  for (int i = 0; i < strsSize; i++) {
    free(keys[i]);
  }
  free(keys);
  free(groupIndex);
  free(groupKeys);
  free(groupCounts);
  free(filled);

  *returnSize = groupTotal;
  return result;
}
