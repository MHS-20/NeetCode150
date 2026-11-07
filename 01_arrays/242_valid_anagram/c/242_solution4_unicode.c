/* decodes UTF-8 to code points; C has no native unicode string type */
#include <stdbool.h>
#include <string.h>

typedef struct {
    int codepoint;
    int count;
} CodepointCount;

static int decode_utf8(const unsigned char *s, size_t len, size_t *i) {
    unsigned char c = s[*i];
    int codepoint;
    int extraBytes;

    if ((c & 0x80) == 0) {
        codepoint = c;
        extraBytes = 0;
    } else if ((c & 0xE0) == 0xC0) {
        codepoint = c & 0x1F;
        extraBytes = 1;
    } else if ((c & 0xF0) == 0xE0) {
        codepoint = c & 0x0F;
        extraBytes = 2;
    } else {
        codepoint = c & 0x07;
        extraBytes = 3;
    }

    for (int k = 0; k < extraBytes && *i + 1 < len; k++) {
        (*i)++;
        codepoint = (codepoint << 6) | (s[*i] & 0x3F);
    }

    (*i)++;
    return codepoint;
}

static int find_or_add(CodepointCount *table, int *tableSize, int codepoint) {
    for (int i = 0; i < *tableSize; i++) {
        if (table[i].codepoint == codepoint) {
            return i;
        }
    }
    table[*tableSize].codepoint = codepoint;
    table[*tableSize].count = 0;
    (*tableSize)++;
    return *tableSize - 1;
}

bool isAnagram(char *s, char *t) {
    size_t sLen = strlen(s);
    size_t tLen = strlen(t);

    CodepointCount table[512];
    int tableSize = 0;

    int sCount = 0;
    for (size_t i = 0; i < sLen;) {
        int cp = decode_utf8((unsigned char *)s, sLen, &i);
        table[find_or_add(table, &tableSize, cp)].count++;
        sCount++;
    }

    int tCount = 0;
    for (size_t i = 0; i < tLen;) {
        int cp = decode_utf8((unsigned char *)t, tLen, &i);
        table[find_or_add(table, &tableSize, cp)].count--;
        tCount++;
    }

    if (sCount != tCount) {
        return false;
    }

    for (int i = 0; i < tableSize; i++) {
        if (table[i].count != 0) {
            return false;
        }
    }

    return true;
}
