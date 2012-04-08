#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t search(const char* str, const size_t k, char c)
{
    /*fprintf(stderr, "  search(%s, %zd)\n", str, k);*/
    size_t positions[k], i = 0, j = 0, len = 0;
    memset(positions, 0, sizeof(positions));
    while (str[i]) {
        if (str[i] == c) {
            const size_t end = j % k;
            const size_t start = (end < (k - 1)) ? end + 1 : end - k + 1;
            positions[end] = i;
            const size_t d = positions[end] - positions[start];
            len = (j < k) ? d : d < len ? d: len;
            /*size_t l = 0;*/
            /*fprintf(stderr, "j=%zd i=%zd start=%zd end=%zd", j, i, start, end);*/
            /*for (; l < k; ++l) {*/
                /*fprintf(stderr, " pos[%zd]=%zd", l, positions[l]);*/
            /*}*/
            /*fprintf(stderr, " len=%zd\n", len);*/
            ++j;
        }
        ++i;
    }
    return j < k ? 0 : len + 1;
}

int main(int ac, char* av[])
{
    if (ac < 3) {
        return 1;
    }
    fprintf(stdout, "%zd\n", search(av[2], atoi(av[1]), '1'));
    return 0;
}
