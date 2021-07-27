#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 1024
#define N 256



int main (int argc, char **argv) {
    char *filename = NULL;
    char *sub_map[N] = {NULL};
    char key, *value, buffer[M], result[M] = {'\0'};
    int i, j, len, index, c;
    int status = 0;

    sub_map['.'] = "STOP";
    sub_map[','] = "PAUSE";
    sub_map['?'] = "QUERY";

    while((c = getopt(argc, argv, "c:")) != EOF) {
        // parse substitutions map
        switch (c) {
            case 'c':
                len = strlen(optarg);
                if (len > 1) {
                    sub_map[optarg[0] & 255] = optarg + 1;
                }
                break;
        }
    }

    if (status) {
	    fprintf(stderr, "usage: %s {-c charstring file ... | -}\n", argv[0]);
	    return(status);
    }

    for (index = optind; index < argc; index++) {
        // parse filename
        filename = argv[index];
    }

    if (filename != NULL) {
        // read from file
        FILE *fp = NULL;
        fp = fopen(filename, "r");
        if (fp != NULL) {
            i = 0;
            while (fgets(buffer+i, sizeof(buffer), fp)) {
                i += strlen(buffer);
            }
            fclose(fp);
        } else {
            perror("open file failed");
            return 1;
        }
    } else {
        // read from stdin
        printf("Enter the message: ");
        fgets(buffer, sizeof(buffer), stdin);
    }

    // convert
    len = strlen(buffer);
    for (i = 0, j = 0; i < len && j < M; ++i, ++j) {
        if (sub_map[buffer[i] & 255] != NULL) {
            // need to substitute
            result[j] = ' ';
            ++j;

            strcpy(result+j, sub_map[buffer[i] & 255]);
            j += strlen(sub_map[buffer[i] & 255]);
            result[j] = ' ';

            if (i + 1 < len && buffer[i+1] == ' ') {
                i++;
            }
        } else {
            result[j] = buffer[i];
        }
    }

    printf("%s\n", result);
    return 0;
}