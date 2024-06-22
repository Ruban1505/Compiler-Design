#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Symbol {
    char name[50];
    int value;
    struct Symbol* next;
} Symbol;

typedef struct {
    Symbol* table[TABLE_SIZE];
} SymbolTable;

// Hash function to map names to table indices
unsigned int hash(char* name) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash << 5) + *name++;
    }
    return hash % TABLE_SIZE;
}

// Initialize symbol table
SymbolTable* createSymbolTable() {
    SymbolTable* symTable = (SymbolTable*)malloc(sizeof(SymbolTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        symTable->table[i] = NULL;
    }
    return symTable;
}

// Add symbol to the symbol table
void addSymbol(SymbolTable* symTable, char* name, int value) {
    unsigned int index = hash(name);
    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    newSymbol->value = value;
    newSymbol->next = symTable->table[index];
    symTable->table[index] = newSymbol;
}

// Remove symbol from the symbol table
void removeSymbol(SymbolTable* symTable, char* name) {
    unsigned int index = hash(name);
    Symbol* current = symTable->table[index];
    Symbol* prev = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Symbol not found: %s\n", name);
        return;
    }

    if (prev == NULL) {
        symTable->table[index] = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Symbol removed: %s\n", name);
}

// Retrieve symbol information from the symbol table
Symbol* getSymbol(SymbolTable* symTable, char* name) {
    unsigned int index = hash(name);
    Symbol* current = symTable->table[index];

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Print the symbol table
void printSymbolTable(SymbolTable* symTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol* current = symTable->table[i];
        if (current != NULL) {
            printf("Index %d:\n", i);
            while (current != NULL) {
                printf("  Name: %s, Value: %d\n", current->name, current->value);
                current = current->next;
            }
        }
    }
}

int main() {
    SymbolTable* symTable = createSymbolTable();

    addSymbol(symTable, "a", 10);
    addSymbol(symTable, "b", 20);
    addSymbol(symTable, "c", 30);

    printf("Symbol Table:\n");
    printSymbolTable(symTable);

    printf("\nRetrieving symbol 'b':\n");
    Symbol* sym = getSymbol(symTable, "b");
    if (sym != NULL) {
        printf("Found symbol - Name: %s, Value: %d\n", sym->name, sym->value);
    } else {
        printf("Symbol not found\n");
    }

    printf("\nRemoving symbol 'b'\n");
    removeSymbol(symTable, "b");

    printf("\nSymbol Table after removing 'b':\n");
    printSymbolTable(symTable);

    // Clean up
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol* current = symTable->table[i];
        while (current != NULL) {
            Symbol* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(symTable);

    return 0;
}

