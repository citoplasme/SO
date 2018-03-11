#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/uio.h>

int main (int argc, char* argv[]) {
	if (argc < 2) exit(1);
	int N = atoi(argv[1]);
	//char buff[N];
	char* buff = malloc(N);
	while (1){
		int n = read(0, buff,N);
		if (n <= 0) break;
		write(1, buff, n);	
	}
	return 0;
}
