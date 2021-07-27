#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define M 1024

// Usage: gcc findnonascii.c -o findnonascii && ./findnonascii .

int dir_walker(char *);
int contains_nonascii(char *);

int main(int argc, char **argv) {
    char *filename = NULL;
    int index;

    if (argc < 2) {
        fprintf(stderr, "usage: %s path1 [path2 ...]\n", argv[0]);
        return 1;
    }

    getopt(argc, argv, ":");
    for (index = optind; index < argc; index++) {
        filename = argv[index];
        dir_walker(filename);
    }

    return 0;
}

int dir_walker(char *dir) {
    // traverse directory recursively
    struct dirent *entry;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(dir);

    if (dr == NULL) {
        printf("Could not open current directory");
        return 0;
    }

    while ((entry = readdir(dr)) != NULL) {
        char path[M];
        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0)
                continue;
            dir_walker(path);
        }

        if (contains_nonascii(entry->d_name)) printf("%s\n", path);
    }

    closedir(dr);
    return 0;
}

int contains_nonascii(char *str) {
    // check str contains non-ascii character
    int i, len = strlen(str);
    for (i = 0; i < len; ++i) {
        if (!isascii(str[i])) {
            return 1;
        }
    }

    return 0;
}