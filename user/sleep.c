#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int i;

    if (argc < 2 || argc > 3) {
        fprintf(2, "Usage: sleep number, where number is an integer.\n");
        exit(1);
    }

    i = atoi(argv[1]);
    sleep(i);
    exit(0);
}