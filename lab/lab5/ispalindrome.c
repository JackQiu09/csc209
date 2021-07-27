#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s string\n", argv[0]);
    }

    int n = strlen(argv[1]);
    char *p = argv[1];
    char *q = p + (n - 1);

    while (p < q) {
        while (isalnum(*p) == 1) {
            p++;
        }
        while (isalnum(*q) == 1) {
            q--;
        }
        
    }
}