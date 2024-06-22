#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 31

int isValidIdentifier(char *identifier) {
    int length = strlen(identifier);
    
    // Check if the identifier is empty or too long
    if (length == 0 || length > MAX_IDENTIFIER_LENGTH) {
        return 0;
    }

    // Check the first character
    if (!(isalpha(identifier[0]) || identifier[0] == '_')) {
        return 0;
    }

    // Check the remaining characters
    for (int i = 1; i < length; i++) {
        if (!(isalnum(identifier[i]) || identifier[i] == '_')) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char identifier[MAX_IDENTIFIER_LENGTH + 1];

    printf("Enter an identifier: ");
    scanf("%s", identifier);

    if (isValidIdentifier(identifier)) {
        printf("'%s' is a valid identifier.\n", identifier);
    } else {
        printf("'%s' is not a valid identifier.\n", identifier);
    }

    return 0;
}

