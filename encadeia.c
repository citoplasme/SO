#include <unistd.h>

// ./a.out ls sort wc

int main(int argc, char* argv[]) {
	int fd[2];
	int i;
	for(i = 1; i < argc-1 ; i++) {
		pipe(fd); // cria um pipe com o par fd
		if(!fork()) { // Se for um filho
			close(fd[0]); // fecha o file descriptor 0
			dup2(fd[1],1); // direciona o conteúdo de fd[1] para o stdoutput
			close(fd[1]); // fecha o 1
			execlp(argv[i], argv[i], (char*) 0); // executa o comando em argv[i]
			_exit(1); // sai
		}
		dup2(fd[0],0); // direciona o conteúdo de fd[0] para o stdinput
		close(fd[0]); // fecha 0
		close(fd[1]); // fecha 1
	}
	execlp(argv[i], argv[i], (char*) 0); // pai executa o ultimo comando
}