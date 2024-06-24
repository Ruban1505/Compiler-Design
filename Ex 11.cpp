#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10
#define MAX_LENGTH 100

typedef struct {
    char lhs;
    char rhs[MAX_RULES][MAX_LENGTH];
    int count;
} Production;

void eliminateLeftRecursion(Production *p) {
    char lhs = p->lhs;
    char alpha[MAX_RULES][MAX_LENGTH];
    char beta[MAX_RULES][MAX_LENGTH];
    int alphaCount = 0, betaCount = 0;

    // Separate productions into alpha and beta
    for (int i = 0; i < p->count; i++) {
        if (p->rhs[i][0] == lhs) {
            strcpy(alpha[alphaCount++], p->rhs[i] + 1);
        } else {
            strcpy(beta[betaCount++], p->rhs[i]);
        }
    }

    // Create new productions
    if (alphaCount > 0) {
        printf("%c -> ", lhs);
        for (int i = 0; i < betaCount; i++) {
            printf("%s%c' ", beta[i], lhs);
            if (i < betaCount - 1) {
                printf("| ");
            }
        }
        printf("\n");

        printf("%c' -> ", lhs);
        for (int i = 0; i < alphaCount; i++) {
            printf("%s%c' ", alpha[i], lhs);
            if (i < alphaCount - 1) {
                printf("| ");
            }
        }
        printf("| e\n");
    } else {
        printf("No left recursion in the given production.\n");
    }
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

    printf("Production after eliminating left recursion:\n");
    eliminateLeftRecursion(&p);

    return 0;
}

