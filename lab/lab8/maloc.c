#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    extern char *duplicate_string();

    char str[1000];
    str[0] = 'h';
    printf("%s\n", duplicate_string(str));
}

char *duplicate_string(char *s)
	{
	    char *p = malloc(strlen(s) + 1);
	    strcpy(p, s);
	    return(p);
	}