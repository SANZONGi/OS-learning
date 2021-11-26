#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
int
main(int argc,char *argv[])
{
    if(argc > 2){
        printf("参数错误\n");
        exit(1);
    }
    int pid;
    //0 read,1 write
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    pid = fork();
    if(pid == 0){
        char buf[5];
        close(fd1[0]);
        close(fd2[1]);
        read(fd2[0],buf,4);
        close(fd2[0]);
        printf("%d: received %s\n",getpid(),buf);
        write(fd1[1],"pong",4);
        close(fd1[1]);
    } else {
        char buf[5];
        close(fd1[1]);
        close(fd2[0]);
        write(fd2[1],"ping",4);
        close(fd2[1]);
        read(fd1[0],buf,4);
        printf("%d: received %s\n",getpid(),buf);
        close(fd1[0]);

    }
    exit(0);
    return 0;
}