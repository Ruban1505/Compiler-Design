#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100
#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    char type[MAX_NAME_LEN];
    int scope;
} Symbol;

typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

void initializeSymbolTable(SymbolTable *table) {
    table->count = 0;
}

int addSymbol(SymbolTable *table, const char *name, const char *type, int scope) {
    if (table->count >= MAX_SYMBOLS) {
        printf("Symbol table is full.\n");
        return 0;
    }
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            printf("Symbol '%s' already exists.\n", name);
            return 0;
        }
    }
    strcpy(table->symbols[table->count].name, name);
    strcpy(table->symbols[table->count].type, type);
    table->symbols[table->count].scope = scope;
    table->count++;
    return 1;
}

int removeSymbol(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            for (int j = i; j < table->count - 1; j++) {
                table->symbols[j] = table->symbols[j + 1];
            }
            table->count--;
            return 1;
        }
    }
    printf("Symbol '%s' not found.\n", name);
    return 0;
}

Symbol* findSymbol(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return &table->symbols[i];
        }
    }
    return NULL;
}

void printSymbolTable(SymbolTable *table) {
    printf("Symbol Table:\n");
    printf("Name\tType\tScope\n");
    for (int i = 0; i < table->count; i++) {
        printf("%s\t%s\t%d\n", table->symbols[i].name, table->symbols[i].type, table->symbols[i].scope);
    }
}

int main() {
    SymbolTable table;
    initializeSymbolTable(&table);

    int choice;
    char name[MAX_NAME_LEN];
    char type[MAX_NAME_LEN];
    int scope;

    while (1) {
        printf("\nSymbol Table Operations:\n");
        printf("1. Add Symbol\n");
        printf("2. Remove Symbol\n");
        printf("3. Find Symbol\n");
        printf("4. Print Symbol Table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter type: ");
                scanf("%s", type);
                printf("Enter scope: ");
                scanf("%d", &scope);
                if (addSymbol(&table, name, type, scope)) {
                    printf("Symbol added successfully.\n");
                }
                break;
            case 2:
                printf("Enter name of the symbol to remove: ");
                scanf("%s", name);
                if (removeSymbol(&table, name)) {
                    printf("Symbol removed successfully.\n");
                }
                break;
            case 3:
                printf("Enter name of the symbol to find: ");
                scanf("%s", name);
                Symbol *symbol = findSymbol(&table, name);
                if (symbol) {
                    printf("Symbol found: %s, Type: %s, Scope: %d\n", symbol->name, symbol->type, symbol->scope);
                } else {
                    printf("Symbol not found.\n");
                }
                break;
            case 4:
                printSymbolTable(&table);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

