struct filematch {
    char *filename;
    struct filematch *next;
};

extern struct filematch *myglob(char *pat);
extern void freemyglob(struct filematch *p);