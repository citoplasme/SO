#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/uio.h>

#define BUF_SIZE 1024

char buf[BUF_SIZE];

int main() {
	char* myfifo = "/tmp/myfifo";
	int x = mkfifo(myfifo, 0602);
	int log = open("LOG", O_WRONLY | O_APPEND | O_CREAT, 0602);
	while(1) {
		int fd = open(myfifo, O_RDONLY);
		while(1) {
        	int n = read(fd, buf, BUF_SIZE);
        	if (n <= 0) break;
        	write(log, buf, BUF_SIZE);
    	}
    	close(fd);
	}
}