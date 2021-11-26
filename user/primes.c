#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

void prime(int fd[2]) {
    int ft[2];
    close(fd[1]);
    int buf, t;

    if (read(fd[0], &buf, sizeof(int))) {
        fprintf(1,"prime %d\n", buf);
        pipe(ft);

        int pid = fork();
        if (pid == 0) {
            prime(ft);
        } else {
            close(ft[0]);
            while (read(fd[0], &t, sizeof(int))) {
                if (t % buf != 0) {
                    write(ft[1], &t, sizeof(int));
                }
            }
            close(fd[0]);
            close(ft[1]);
            wait(0);
        }
    }
    exit(0);
}

int
main(int argc, char *argv[]) {

    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid == 0) {
        prime(fd);
    } else {
        close(fd[0]);
        for (int i = 2; i <= 35; i++) {
            write(fd[1], &i, sizeof(int));
        }
        close(fd[1]);
        wait(0);
    }
    exit(0);
}