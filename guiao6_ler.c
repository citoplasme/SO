#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/uio.h>
//int mkfifo(const char *pathname, mode_t mode);

#define BUF_SIZE 256

int main() {
    char* myfifo = "/tmp/myfifo2";
    char buf[BUF_SIZE] = "";
    int fd = open(myfifo, O_RDONLY);
    while(1) {
        int n = read(fd, buf, BUF_SIZE);
        if (n <= 0) break;
        write(0, buf, BUF_SIZE);
    }
    close(fd);
    _exit(1);
	return 0;
}