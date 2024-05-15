#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAX_ARG_LEN 32

int
main(int argc, char *argv[])
{
    char *buf[MAXARG];
    int i;

    if (argc < 2) {
        fprintf(2, "Usage: xargs <command>\n");
        exit(1);
    }

    for (i = 1; i < argc; i++) {
        buf[i - 1] = argv[i];
    }

    char *p;
    i--;
    buf[i] = (char *)malloc(MAX_ARG_LEN * sizeof(char));
    p = buf[i];
    while (read(0, p, sizeof(char)) > 0) {
        if (*p == '\n' || *p == '\0' || *p == ' ') {
            *p = '\0';
            i++;
            buf[i] = (char *)malloc(MAX_ARG_LEN * sizeof(char));
            p = buf[i];
            continue;
        }
        p++;
    }

    if (fork() == 0) {
        exec(buf[0], buf);
    } else {
        wait(0);
    }
    exit(0);
}