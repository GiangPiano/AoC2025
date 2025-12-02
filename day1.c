#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 64
#define MAX_LINE_LEN 64

char** read_file(const char *filename, size_t* line_count) 
{
    FILE *fptr = fopen(filename, "r");
    if (!fptr) return NULL;

    size_t count = 0;
    size_t capacity = INITIAL_CAPACITY;

    char** lines = malloc(capacity * sizeof(char*));
    char buffer[MAX_LINE_LEN];

    while (fgets(buffer, sizeof buffer, fptr))
    {
        if (count >= capacity) {
            capacity *= 2;
            char **new_lines = realloc(lines, capacity * sizeof(char*));
            lines = new_lines;
        }

        lines[count] = malloc(strlen(buffer) + 1);
        strcpy(lines[count], buffer);

        count++;
    }
    *line_count = count;

    fclose(fptr);
    return lines;
}

int main(int argc, char *argv[])
{
    size_t line_count = 0;
    char** lines = read_file("input.txt", &line_count);
    int dial = 50;
    int res = 0;
    for (int i = 0; i < line_count; i++)
    {
        char ini = lines[i][0];
        int val = strtol(lines[i] + 1, NULL, 10);

        int old = dial;
        dial = ini == 'L' ? dial - val : dial + val;

        res += abs(dial / 100) + (old * dial < 0);
        
        if (dial == 0) res++;
        dial %= 100;
        printf("%s %d -> %d (%d)\n", lines[i], old, dial, res);
    }

    printf("%d", res);

    return 0;
}
