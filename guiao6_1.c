//RWX RWX RWX >> Valores de bits que em hexa são as permissões, ex: 0666

// lsof 
// lsof -c cat
// lsof -p NUMERO_PROCESSO

// open em fifo bloqueia ate haver sincronizacao do open

// fork cria outra bash

// echo "qq coisa" > tmp/fifo

// cat < /tmp/fifo >> /tmp/log // MODO APPEND >>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/uio.h>
//int mkfifo(const char *pathname, mode_t mode);

#define BUF_SIZE 1024

int myfifo() {
	char* myfifo = "/tmp/myfifo";
	int x = mkfifo(myfifo, 0602);
	return x;
}

#define BUF_SIZE 1024

int main() {
	char* myfifo = "/tmp/myfifo2";
	int x = mkfifo(myfifo, 0602);
	char buf[BUF_SIZE] = "";
	int fd = open(myfifo, O_WRONLY);
	while(1) {
		int n = read(0, buf, BUF_SIZE);
		if (n <= 0) break;
		write(fd, buf, BUF_SIZE);
	}
	close(fd);
	_exit(1);
	return 0;
}