#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
# include <sys/uio.h>

ssize_t readln_v1(int fildes, void *buf, size_t nbyte) {
    ssize_t nb = 0;
    char* p = buf;
    while (1) {
        if (nb >= nbyte) break;
        int n = read(fildes, p, 1);
        if (n <= 0) break;
        nb += 1;
        if (*p == '\n') break;
        p += 1;
    }
    return nb;
}
