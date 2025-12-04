#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 4096

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input.txt", "r");
    char buffer[MAX_LINE_LEN];
    long long res = 0;
    while (fgets(buffer, sizeof(buffer), fp)) 
    {
        int len = strlen(buffer);
        char s[12] = "000000000000";
        int start = -1;
        printf("%s", buffer);
        for (int k = 12; k > 0; k--) 
        {
            for (int i = start + 1; i < len - k; i++) 
            {
                if (buffer[i] > s[12 - k]) 
                {
                    s[12 - k] = buffer[i];
                    start = i;
                }
            }
            printf("%c", s[12 - k]);
        }
        long long max_num = strtol(s, NULL, 10);
        printf("\n");
        // printf("%d\n", max_num);
        res += max_num;
    }
    printf("%lld", res);
    return EXIT_SUCCESS;
}
