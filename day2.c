#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 4096

long long tenth(long long n) 
{
    if (n < 10) return 10;
    if (n < 100) return 100;
    if (n < 1000) return 1000;
    if (n < 10000) return 10000;
    return 100000;
}

long long greater_than_equal(long long a[], size_t sz, long long val)
{
    long long l = 0, r = (long long)sz - 1;
    long long res = 0;
    while (l <= r) 
    {
        long long mid = (l + r + 1) >> 1;
        if (a[mid] >= val) 
        {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }

    return res;
}

long long smaller_than_equal(long long a[], size_t sz, long long val)
{
    long long l = 0, r = (long long)sz - 1;
    long long res = 0;

    while (l <= r) 
    {
        long long mid = (l + r) >> 1;
        if (a[mid] <= val) 
        {
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }

    return res;
}

int comp(const void *a, const void *b)
{
    long long x = *(const long long *)a;
    long long y = *(const long long *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    // INIT
    size_t limits[11] = {
        0,
        0,
        99999,   // k=2
        9999,    // k=3
        999,     // k=4
        999,     // k=5
        999,     // k=6
        999,     // k=7
        999,     // k=8
        999,     // k=9
        999      // k=10* tenth(i)
    };

    size_t N = 0;
    for (int k = 2; k <= 10; k++) N += limits[k];

    long long *invalid = calloc(N, sizeof(long long));
    size_t pos = 0;

    for (int k = 2; k <= 10; k++) {
        size_t max_i = limits[k];
        for (long long i = 1; i <= max_i; i++) {
            long long B = tenth(i);
            long long v = 0;
            long long p = 1;
            for (int t = 0; t < k; t++) {
                v += i * p;
                p *= B;
            }
            invalid[pos++] = v;
        }
    }
    qsort(invalid, N, sizeof(invalid[0]), comp);

    // dedupe
    size_t uniq = 0;
    for (size_t i = 0; i < N; i++) {
        if (i == 0 || invalid[i] != invalid[i - 1]) {
            invalid[uniq++] = invalid[i];
        }
    }
    N = uniq;

    long long *prefix = calloc(N + 1, sizeof(long long));
    for (long long i = 1; i < N; i++) 
    {
        prefix[i] = prefix[i - 1] + invalid[i];
    }

    FILE *fp = fopen("input.txt", "r");
    char buffer[MAX_LINE_LEN];
    fgets(buffer, sizeof(buffer), fp);
    char *str = malloc(strlen(buffer) + 1);
    strcpy(str, buffer);

    // PARSING
    char *token = strtok(str, ",");
    long long res = 0;
    while (token != NULL) 
    {
        long long left, right;
        sscanf(token, "%lld-%lld", &left, &right);
        long long left_bound = greater_than_equal(invalid, N, left);
        long long right_bound = smaller_than_equal(invalid, N, right);

        printf("[%lld, %lld] ", left, right);
        printf("%lld -> %lld", invalid[left_bound], invalid[right_bound]);
        long long old_res = res;

        res += (prefix[right_bound] - prefix[left_bound - 1]) >= 0 ? prefix[right_bound] - prefix[left_bound - 1] : 0;
        printf(": %lld", res - old_res);
        printf("\n");

        token = strtok(NULL, ",");
    }

    printf("%lld", res);

    return EXIT_SUCCESS;
}
