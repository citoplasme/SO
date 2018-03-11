#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/uio.h>

int main (int argc, char* argv[]) {
	if (argc < 2) exit(1);
	int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	char c = '#';
	for (int i = 0; i < 10000000; i++) {
		write(fd, &c, 1);
	}
	return 0;
}
