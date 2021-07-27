#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myglob.h"

int main()
{
    struct filematch *p;
    char *s = "hello";

    p = malloc(sizeof(struct filematch));
    if (p == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    p->filename = malloc(strlen(s) + 1);
    if (p->filename == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(p->filename, s);
    printf("%s\n", p->filename);
    free(p->filename);
    free(p);

    char *s1 = "helll";
    printf("%d\n", strncmp(s, s1, 5));

    return(0);
}