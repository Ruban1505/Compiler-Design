#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 31

void skipWhitespaceAndComments(FILE *file) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) {
            continue;
        }
        if (c == '/') {
            int next = fgetc(file);
            if (next == '/') {
                while ((c = fgetc(file)) != EOF && c != '\n');
            } else if (next == '*') {
                while ((c = fgetc(file)) != EOF) {
                    if (c == '*' && (next = fgetc(file)) == '/') {
                        break;
                    }
                }
            } else {
                ungetc(next, file);
                ungetc(c, file);
                break;
            }
        } else {
            ungetc(c, file);
            break;
        }
    }
}

void handleIdentifierOrKeyword(FILE *file, int c) {
    char buffer[MAX_IDENTIFIER_LENGTH + 1];
    int i = 0;

    do {
        if (i < MAX_IDENTIFIER_LENGTH) {
            buffer[i++] = c;
        }
        c = fgetc(file);
    } while (isalnum(c) || c == '_');

    buffer[i] = '\0';
    ungetc(c, file);

    printf("Identifier: %s\n", buffer);
}

void handleNumber(FILE *file, int c) {
    char buffer[32];
    int i = 0;

    do {
        buffer[i++] = c;
        c = fgetc(file);
    } while (isdigit(c));

    buffer[i] = '\0';
    ungetc(c, file);

    printf("Constant: %s\n", buffer);
}

void handleOperator(int c) {
    printf("Operator: %c\n", c);
}

void lexicalAnalyzer(FILE *file) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        skipWhitespaceAndComments(file);
        if (isalpha(c) || c == '_') {
            handleIdentifierOrKeyword(file, c);
        } else if (isdigit(c)) {
            handleNumber(file, c);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            handleOperator(c);
        }
    }
}

int main() {
    FILE *file = fopen("code.c", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    lexicalAnalyzer(file);

    fclose(file);
    return 0;
}

