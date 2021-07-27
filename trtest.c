#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd[2], r;

    /* Create the pipe */
    if ((pipe(fd)) == -1) {
        perror("pipe");
        exit(1);
    }

    if ((r = fork()) > 0) {
        
        if ((dup2(fd[0], fileno(stdin))) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd[0]);
        close(fd[1]);
    execl("/usr/bin/tr", "tr", "e", "f", (char *)NULL);
	perror("/usr/bin/tr");
	exit(1);

    } else if (r == 0) {

        if ((dup2(fd[1], fileno(stdout))) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd[1]);
        close(fd[0]);

        write(fileno(stdout), "hello\n", 6);
	exit(1);

    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}