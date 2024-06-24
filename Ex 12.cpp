#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RULES 10
#define MAX_LENGTH 100

typedef struct {
    char lhs;
    char rhs[MAX_RULES][MAX_LENGTH];
    int count;
} Production;

void eliminateLeftFactoring(Production *p) {
    char lhs = p->lhs;
    char prefix[MAX_LENGTH] = "";
    int prefixLen = 0;
    
    // Find the common prefix
    for (int i = 0; i < p->count - 1; i++) {
        for (int j = i + 1; j < p->count; j++) {
            int k = 0;
            while (p->rhs[i][k] != '\0' && p->rhs[j][k] != '\0' && p->rhs[i][k] == p->rhs[j][k]) {
                k++;
            }
            if (k > prefixLen) {
                prefixLen = k;
                strncpy(prefix, p->rhs[i], prefixLen);
                prefix[prefixLen] = '\0';
            }
        }
    }

    // If no common prefix found, no left factoring is needed
    if (prefixLen == 0) {
        printf("No left factoring needed for the given production.\n");
        return;
    }

    // Create new productions
    printf("%c -> %s%c'\n", lhs, prefix, lhs);
    printf("%c' -> ", lhs);
    for (int i = 0; i < p->count; i++) {
        if (strncmp(p->rhs[i], prefix, prefixLen) == 0) {
            printf("%s ", p->rhs[i] + prefixLen);
        } else {
            printf("%s ", p->rhs[i]);
        }
        if (i < p->count - 1) {
            printf("| ");
        }
    }
    printf("\n");
}

int main() {
    Production p;
    p.count = 0;

    printf("Enter the left-hand side of the production (single non-terminal): ");
    scanf(" %c", &p.lhs);

    printf("Enter the number of right-hand side productions: ");
    scanf("%d", &p.count);

    printf("Enter the right-hand side productions (one per line):\n");
    for (int i = 0; i < p.count; i++) {
        scanf("%s", p.rhs[i]);
    }

    printf("\nOriginal Production:\n");
    printf("%c -> ", p.lhs);
    for (int i = 0; i < p.count; i++) {
        printf("%s ", p.rhs[i]);
        if (i < p.count - 1) {
            printf("| ");
        }
    }
    printf("\n\n");

    printf("Production after eliminating left factoring:\n");
    eliminateLeftFactoring(&p);

    return 0;
}

