#include <stdio.h>

void countWhitespaceAndNewlines(FILE *file, int *whitespaceCount, int *newlineCount) {
    int c;
    *whitespaceCount = 0;
    *newlineCount = 0;
    
    while ((c = fgetc(file)) != EOF) {
        if (c == ' ' || c == '\t') {
            (*whitespaceCount)++;
        } else if (c == '\n') {
            (*newlineCount)++;
        }
    }
}

int main() {
    FILE *file = fopen("code.c", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    int whitespaceCount, newlineCount;
    countWhitespaceAndNewlines(file, &whitespaceCount, &newlineCount);

    printf("Number of whitespace characters: %d\n", whitespaceCount);
    printf("Number of newline characters: %d\n", newlineCount);

    fclose(file);
    return 0;
}

