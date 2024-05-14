#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p1[2], p2[2];
    int pid;
    char buf[8];
    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        close(p1[1]);
        close(p2[0]);
        if (read(p1[0], buf, 8) > 0) {
            pid = getpid();
            printf("%d: received ping\n", pid);
            write(p2[1], buf, 8);
        }
        close(p1[0]);
        close(p2[1]);
    } else {
        close(p1[0]);
        close(p2[1]);
        write(p1[1], "Ping!\n", 8);
        if (read(p2[0], buf, 8) > 0) {
            pid = getpid();
            printf("%d: received pong\n", pid);
        }
        close(p1[1]);
        close(p2[0]);
    }
    exit(0);
}