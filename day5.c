#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 64
typedef struct {
    long long left;
    long long right;
} Range;

int range_comp(const void* a, const void* b) {
    const Range* range_a = (const Range*)a;
    const Range* range_b = (const Range*)b;

    if (range_a->left == range_b->left) return range_a->right >= range_b->right ? 1 : -1;
    return range_a->left >= range_b->left ? 1 : -1;
}

int main(int argc, char* argv[]) {
    FILE* fp = fopen("input.txt", "r");
    char* line = NULL;
    size_t cap = 0;
    ssize_t len;

    Range range[10000];
    long long range_count = 0;
    while ((len = getline(&line, &cap, fp)) > 1) {
        sscanf(line, "%lld-%lld", &range[range_count].left, &range[range_count].right);
        range_count++;
    }

    long long id[10000];
    long long id_count = 0;
    while ((len = getline(&line, &cap, fp)) > 1) {
        sscanf(line, "%lld", &id[id_count]);
        id_count++;
    }
    fclose(fp);

    range[range_count++] =
        (Range){.left = 100000000000000000, .right = 100000000000000000};  // placeholder
    qsort(range, range_count, sizeof(Range), range_comp);

    long long curr_l = range[0].left;
    long long curr_r = range[0].right;
    long long res = 0;

    for (int i = 1; i < range_count; i++) {
        if (range[i].left > curr_r || i == range_count - 1) {
            res += curr_r - curr_l + 1;
            // printf("Concatenated range: %lld - %lld (Length: %lld)\n", curr_l, curr_r, curr_r -
            // curr_l + 1);
            curr_l = range[i].left;
        }
        curr_r = range[i].right > curr_r ? range[i].right : curr_r;
    }

    printf("%lld", res);

    return EXIT_SUCCESS;
}
