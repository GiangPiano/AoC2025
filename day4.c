#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 64
#define MAX_LINE_LEN 1024

char** read_file(const char *filename, size_t *line_count)
{
    FILE *fptr = fopen(filename, "r");
    if (!fptr) return NULL;

    size_t count = 0;
    size_t capacity = INITIAL_CAPACITY;

    char **lines = malloc(capacity * sizeof(char*));
    if (!lines) {
        fclose(fptr);
        return NULL;
    }

    char buffer[MAX_LINE_LEN];

    while (fgets(buffer, sizeof buffer, fptr))
    {
        if (count == capacity) {
            size_t newcap = capacity * 2;
            char **tmp = realloc(lines, newcap * sizeof(char*));
            if (!tmp) {
                // cleanup previous allocations
                for (size_t i = 0; i < count; i++) {
                    free(lines[i]);
                }
                free(lines);
                fclose(fptr);
                return NULL;
            }
            lines = tmp;
            capacity = newcap;
        }

        size_t len = strlen(buffer);
        lines[count] = malloc(len + 1);
        if (!lines[count]) {
            // cleanup previous allocations
            for (size_t i = 0; i < count; i++) {
                free(lines[i]);
            }
            free(lines);
            fclose(fptr);
            return NULL;
        }

        memcpy(lines[count], buffer, len + 1); // includes '\0'
        count++;
    }

    fclose(fptr);
    *line_count = count;
    return lines;
}

int main(int argc, char *argv[])
{
    size_t line_count;
    char **grid = read_file("input.txt", &line_count);

    int height = line_count, width = strlen(grid[0]) - 1;
    int count[height][width];
    int removed = 0;
    while (1) {
        int change = 0;
        memset(count, 0, sizeof(count));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j] == '@') {
                    count[i][j]++;
                    count[i][j] += (i + 1 < height && grid[i + 1][j] == '@');
                    count[i][j] += (i - 1 >= 0 && grid[i - 1][j] == '@');
                    count[i][j] += (j + 1 < width && grid[i][j + 1] == '@');
                    count[i][j] += (j - 1 >= 0 && grid[i][j - 1] == '@');
                    count[i][j] += (i + 1 < height && j + 1 < width && grid[i + 1][j + 1] == '@');
                    count[i][j] += (i + 1 < height && j - 1 >= 0 && grid[i + 1][j - 1] == '@');
                    count[i][j] += (i - 1 >= 0 && j + 1 < width && grid[i - 1][j + 1] == '@');
                    count[i][j] += (i - 1 >= 0 && j - 1 >= 0 && grid[i - 1][j - 1] == '@');
                }
            }
        }

        // int change = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (count[i][j] <= 4 && count[i][j] != 0) {
                    grid[i][j] = '.';
                    change++;
                }
            }
        }
        removed += change;
        printf("Removed %d rolls of paper", change);
        if (change == 0) break;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                // printf("%d", count[i][j]);
                printf("%c", (count[i][j] > 4 ? '@' : (count[i][j] == 0 ? '.' : 'x')));
            }
            printf("\n");
        }
        printf("\n");
    }

    printf("%d", removed);

    return EXIT_SUCCESS;
}
