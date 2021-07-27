#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define M 1024
#define N 256

void process(FILE *, char **);

int main(int argc, char **argv) {
    char *filename = NULL;
    char *sub_map[N] = {NULL};
    char key, *value = {'\0'};
    int len, index, c;
    FILE *fp;

    // set default values
    sub_map[(int)','] = "PAUSE";
    sub_map[(int)'.'] = "STOP";
    sub_map[(int)'?'] = "QUERY";

    while ((c = getopt(argc, argv, "c:")) != EOF) {
        // parse substitutions map
        switch (c) {
            case 'c':
                len = strlen(optarg);
                if (len > 1) {
                    key = optarg[0];
                    value = malloc(len);
                    strcpy(value, optarg + 1);
                    sub_map[(int)key] = value;
                }

                break;
        }
    }
    
    if (argc == 1) {
        process(stdin, sub_map);
    }

    for (index = optind; index < argc; index++) {
        // parse filename
        filename = argv[index];

        if (strcmp(filename, "-") == 0) {
            process(stdin, sub_map);
        } else if ((fp = fopen(filename, "r")) == NULL) {
            perror(filename);
            return 1;
        } else {
            process(fp, sub_map);
            fclose(fp);
        }
    }

    return 0;
}

void process(FILE *fp, char **sub_map) {
    char buffer[M], result[M] = {'\0'};
    int i, j, len;

    // read from file
    if (fp == stdin) {
        fgets(buffer, sizeof(buffer), fp);
    } else {
        i = 0;
        while (fgets(buffer + i, sizeof(buffer), fp)) {
            i += strlen(buffer);
        }
    }

    // convert
    len = strlen(buffer);
    for (i = 0, j = 0; i < len && j < M; ++i, ++j) {
        if (sub_map[(int)buffer[i]] != NULL) {
            // need to substitute
            result[j] = ' ';
            ++j;

            strcpy(result + j, sub_map[(int)buffer[i]]);
            j += strlen(sub_map[(int)buffer[i]]);
            result[j] = ' ';

            if (i + 1 < len && buffer[i + 1] == ' ') {
                i++;
            }
        } else {
            result[j] = buffer[i];
        }
    }

    printf("%s", result);
}