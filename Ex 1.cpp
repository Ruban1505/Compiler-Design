#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Define token types
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_CONSTANT,
    TOKEN_OPERATOR,
    TOKEN_UNKNOWN
} TokenType;

// Structure to store token attributes
typedef struct {
    TokenType type;
    char attribute[50];
} Token;

// Function prototypes
Token getNextToken(const char **input);
void printToken(Token token);
int isOperator(char c);

// Main function
int main() {
    const char *input = "int x = 10 + 20;";
    const char *ptr = input;
    Token token;

    printf("Input: %s\n", input);
    printf("Tokens:\n");

    while (*ptr != '\0') {
        token = getNextToken(&ptr);
        if (token.type != TOKEN_UNKNOWN) {
            printToken(token);
        }
    }

    return 0;
}

// Function to get the next token from the input
Token getNextToken(const char **input) {
    Token token;
    token.type = TOKEN_UNKNOWN;
    char buffer[50];
    int i = 0;

    // Skip whitespace
    while (isspace(**input)) {
        (*input)++;
    }

    // Check for end of input
    if (**input == '\0') {
        return token;
    }

    // Identify and extract tokens
    if (isalpha(**input)) {  // Identifier
        while (isalnum(**input)) {
            buffer[i++] = *(*input)++;
        }
        buffer[i] = '\0';
        token.type = TOKEN_IDENTIFIER;
        strcpy(token.attribute, buffer);
    } else if (isdigit(**input)) {  // Constant
        while (isdigit(**input)) {
            buffer[i++] = *(*input)++;
        }
        buffer[i] = '\0';
        token.type = TOKEN_CONSTANT;
        strcpy(token.attribute, buffer);
    } else if (isOperator(**input)) {  // Operator
        buffer[i++] = *(*input)++;
        buffer[i] = '\0';
        token.type = TOKEN_OPERATOR;
        strcpy(token.attribute, buffer);
    } else {  // Unknown token
        (*input)++;
    }

    return token;
}

// Function to print token information
void printToken(Token token) {
    switch (token.type) {
        case TOKEN_IDENTIFIER:
            printf("Identifier: %s\n", token.attribute);
            break;
        case TOKEN_CONSTANT:
            printf("Constant: %s\n", token.attribute);
            break;
        case TOKEN_OPERATOR:
            printf("Operator: %s\n", token.attribute);
            break;
        default:
            printf("Unknown token\n");
            break;
    }
}

// Function to check if a character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == ';';
}

