#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the symbol structure
typedef struct Symbol {
    char name[50];
    int address;
    struct Symbol *next;
} Symbol;

// Define the symbol table structure
typedef struct {
    Symbol *head;
} SymbolTable;

// Initialize the symbol table
void initializeSymbolTable(SymbolTable *table) {
    table->head = NULL;
}

// Add a new symbol to the symbol table
void addSymbol(SymbolTable *table, char *name, int address) {
    // Create a new symbol
    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    newSymbol->address = address;
    newSymbol->next = table->head;
    table->head = newSymbol;
    printf("Added symbol: %s with address: %d\n", name, address);
}

// Remove a symbol from the symbol table
void removeSymbol(SymbolTable *table, char *name) {
    Symbol *current = table->head;
    Symbol *previous = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Symbol not found: %s\n", name);
        return;
    }

    if (previous == NULL) {
        table->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Removed symbol: %s\n", name);
}

// Retrieve a symbol from the symbol table
Symbol *retrieveSymbol(SymbolTable *table, char *name) {
    Symbol *current = table->head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Display the symbol table
void displaySymbolTable(SymbolTable *table) {
    Symbol *current = table->head;
    printf("Symbol Table:\n");
    printf("Name\tAddress\n");
    while (current != NULL) {
        printf("%s\t%d\n", current->name, current->address);
        current = current->next;
    }
}

int main() {
    SymbolTable table;
    initializeSymbolTable(&table);

    addSymbol(&table, "x", 100);
    addSymbol(&table, "y", 200);
    addSymbol(&table, "z", 300);

    displaySymbolTable(&table);

    Symbol *symbol = retrieveSymbol(&table, "y");
    if (symbol != NULL) {
        printf("Retrieved symbol: %s with address: %d\n", symbol->name, symbol->address);
    } else {
        printf("Symbol not found: y\n");
    }

    removeSymbol(&table, "x");
    displaySymbolTable(&table);

    return 0;
}

