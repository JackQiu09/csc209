#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define M 1024

int main(int argc, char **argv) {
    char *aux_path = NULL, *log_path = NULL, *old_log_path = NULL;
    char c, buffer[M];
    int index, pos, log_size, old_log_size1, old_log_size2;
    int newflag = 0;
    FILE *aux_fp, *log_fp, *old_log_fp;

    while ((c = getopt(argc, argv, "-n")) != -1) {
        // parse substitutions map
        switch (c) {
            case 'n':
                newflag = 1;
                break;
        }
    }

    if (((newflag == 1) && (argc != 5)) || ((newflag == 0) && (argc != 4))) {
        fprintf(stderr, "usage: %s [-n] file1 file2 file3\n", argv[0]);
        return 1;
    }

    index = optind;
    aux_path = argv[index];
    log_path = argv[index + 1];
    old_log_path = argv[index + 2];

    // handle auxiliary file
    if (newflag) {
        if (access(aux_path, F_OK) != 0) {  // not exist
            aux_fp = fopen(aux_path, "w");
            fprintf(aux_fp, "0 0");
            fclose(aux_fp);
        }
    }

    // open files
    aux_fp = fopen(aux_path, "r");
    log_fp = fopen(log_path, "r");
    old_log_fp = fopen(old_log_path, "r");
    if (aux_fp == NULL || log_fp == NULL || old_log_fp == NULL) {
        printf("auxiliary/log/old_log file is not exist\n");
        return 1;
    }

    // read files
    fscanf(aux_fp, "%d %d", &pos, &old_log_size1);
    fclose(aux_fp);

    fseek(log_fp, 0L, SEEK_END);
    log_size = ftell(log_fp);

    fseek(old_log_fp, 0L, SEEK_END);
    old_log_size2 = ftell(old_log_fp);

    if (old_log_size1 < old_log_size2) {
        // rotate
        fseek(old_log_fp, old_log_size1, SEEK_SET);  // seek
        while (fgets(buffer, sizeof(buffer), old_log_fp)) {
            printf("%s", buffer);
        }
    }

    if (log_size < pos) {
        // rotate
        pos = 0;
    }
    fseek(log_fp, pos, SEEK_SET);  // seek
    while (fgets(buffer, sizeof(buffer), log_fp)) {
        printf("%s", buffer);
    }

    // write auxiliary file
    aux_fp = fopen(aux_path, "w");
    fprintf(aux_fp, "%d %d", log_size, old_log_size2);

    return 0;
}