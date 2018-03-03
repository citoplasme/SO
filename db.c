#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>

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

// ./a.out < db.c 
int main () {
    int nl = 1;
    char buff[10000];
    while (1) {
        int x = sprintf(buff, "% 6d  ", nl);
        ssize_t r = readln_v1(0, buff + x, sizeof(buff)-x);
        if (r <= 0) break;
        write(1, buff,x + r);
        nl++;
    }
    return 0;
}
