#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/uio.h>
#include <string.h>

char buf[1000];

int main(int argc, char* argv[]) {
	char* myfifo = "/tmp/myfifo";
	int fd = open(myfifo, O_WRONLY);
	int n = strlen(argv[1] + 2);
	char buf[n];
	memcpy(buf, argv[1], n);
	buf[n - 2] = '\n';
	buf[n - 1] = '\0';
	write(fd, buf, n);
	return 0;
}