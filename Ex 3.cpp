%{
#include <stdio.h>

int space_count = 0;
int newline_count = 0;
int tab_count = 0;
%}

/* Regular expressions for whitespace and newline characters */
%%
" "         { space_count++; }
"\t"        { tab_count++; }
"\n"        { newline_count++; }
/* Match and ignore other characters */
.           { /* ignore other characters */ }
%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Unable to open file");
            return 1;
        }
        yyin = file;
    }

    yylex();
    printf("Spaces: %d\n", space_count);
    printf("Tabs: %d\n", tab_count);
    printf("Newlines: %d\n", newline_count);
    return 0;
}

int yywrap() {
    return 1;
}

