#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "myglob.h"

struct filematch *head = NULL;

struct filematch *myglob(char *pat)
{
    DIR *dp;
    struct dirent *p;
    extern int questionmatch(char *obj, char *pat, int n);
    extern struct filematch *strcmalloc();
    extern char *filemalloc(char *filename);

    if ((dp = opendir(".")) == NULL) {
        perror(".");
        return NULL;
    }

    if (strchr(pat, '*') == NULL) {
        while ((p = readdir(dp))) {
            if (questionmatch(p->d_name, pat, strlen(pat))) {
                struct filematch *pt = strcmalloc();
                pt->filename = filemalloc(p->d_name);
            }
        }
    } else {

    }
    
    

    return head;
}

struct filematch *strcmalloc() {
    struct filematch *pt;
    pt = malloc(sizeof(struct filematch));
    if (pt == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    return pt;
}

char *filemalloc(char *filename) {
    char *fn;
    fn = malloc(strlen(filename) + 1);
    if (fn == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(fn, filename);
    return fn;
}

int questionmatch(char *obj, char *pat, int n)
{
    if (n == 0)
        return 1;
    if (strlen(obj) != strlen(pat)) 
        return 0;
    for (int i = 0; i < n; i++) {
        if (pat[i] == '?') {
            i++;
        } else if (obj[i] != pat[i]) {
            return 0;
        }
    }
    return 1;
}

void freemyglob(struct filematch *pt)
{
    //this should be the correct push
}