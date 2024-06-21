#include <stdio.h>

// Function to print the original grammar
void printOriginalGrammar() {
    printf("Original Grammar:\n");
    printf("A ? aB | aC\n");
}

// Function to print the converted grammar
void printConvertedGrammar() {
    printf("Converted Grammar (Left Factoring Eliminated):\n");
    printf("A  ? aA'\n");
    printf("A' ? B | C\n");
}

int main() {
    // Print the original grammar
    printOriginalGrammar();

    // Print the converted grammar
    printConvertedGrammar();

    return 0;
}

