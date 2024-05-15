#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int read_end);

int
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        primes(p[0]);
        close(p[0]);
    } else {
        close(p[0]);
        int i;
        for (i = 2; i < 36; i++) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
    }
    wait(0);
    exit(0);
}

void
primes(int read_end)
{
    int first;
    if (read(read_end, &first, sizeof(int)) > 0) {
        printf("prime %d\n", first);
    } else {
        return;
    }

    int p[2];
    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        primes(p[0]);
        close(p[0]);
    } else {
        close(p[0]);
        int buf;
        while (read(read_end, &buf, sizeof(int)) > 0) {
            if (buf % first != 0) {
                write(p[1], &buf, sizeof(int));
            }
        }
        close(p[1]);
    }
}