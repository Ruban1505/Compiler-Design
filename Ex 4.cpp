#include <stdio.h>

// Function to print the original grammar
void printOriginalGrammar() {
    printf("Original Grammar:\n");
    printf("S ? Sa | b\n");
}

// Function to print the converted grammar
void printConvertedGrammar() {
    printf("Converted Grammar (Non-Left-Recursive):\n");
    printf("S  ? bS'\n");
    printf("S' ? aS' | e\n");
}

int main() {
    // Print the original grammar
    printOriginalGrammar();

    // Print the converted grammar
    printConvertedGrammar();

    return 0;
}

