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
    extern void insert(char *filename);
    extern int questionmatch(char *obj, char *pat, int n);

    if ((dp = opendir(".")) == NULL) {
        perror(".");
        return NULL;
    }

    if (strchr(pat, '*') == NULL) {
        while ((p = readdir(dp))) {
            if (strlen(p->d_name) == strlen(pat) && questionmatch(p->d_name, pat, strlen(pat))) {
                insert(p->d_name);
            }
        }
        return head;
    } else {
        while ((p = readdir(dp))) {
            int index;
            char *ptr;
            ptr = strchr(pat, '*');
            index = ptr - pat;
            int n = strlen(pat) - 1;
            int slen = strlen(p->d_name);
            if (strlen(p->d_name) >= strlen(pat) - 1) {
                if (index == 0) {
                    if (questionmatch((p->d_name) + (slen - n), pat + 1, n)) {
                        insert(p->d_name);
                    }
                } else if (index == n) {
                    if (questionmatch(p->d_name, pat, index)) {
                        insert(p->d_name);
                    }
                } else {
                    int after = strlen(pat) - index - 1;
                    int i = index + 1;
                    if (questionmatch(p->d_name, pat, index) && questionmatch((p->d_name) + slen - after, pat + i, after)) {
                        insert(p->d_name);
                    }
                }
            }
        }
        closedir(dp);
        return head;
    }
    
    

    return head;
}

void insert(char *filename)
{
    struct filematch *new, **pp;

    if ((new = malloc(sizeof(struct filematch))) == NULL) {
        fprintf(stderr, "out of memory!\n");  /* unlikely */
        exit(1);
    }

    if ((new->filename = malloc(strlen(filename) + 1)) == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    strcpy(new->filename, filename);

    for (pp = &head; *pp; pp = &(*pp)->next)
        ;
    
    new->next = *pp;
    *pp = new;
}


int questionmatch(char *obj, char *pat, int n)
{
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
    while (pt) {
        struct filematch *old = pt;
        pt = pt->next;
        free(old->filename);
        free(old);
        printf("struct freed\n");
    }
}