#include <unistd.h>     /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
/*
int execl(const char *path, const char *arg0, ..., NULL);
int execlp(const char *file, const char *arg0, ..., NULL);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
*/

// 1
void ex_1 () {
	execl("/bin/ls", "ls", "-l", (char *)0);
}

// 2
void ex_2() {
	pid_t pid = fork();
	if (pid == 0) 
		execlp("ls", "ls", "-l", (char*)0);
		exit(0);
}

void ex_3(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++)
		printf("%s ",argv[i]);
	puts("\n");
	
}

void ex_4(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++)
		if (i == 0) printf("IDK ");
		else printf("%s ", argv[i]);
	puts("\n");
}

// ./a.out ls
void ex_5(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++)
		if (!fork())
			execlp(argv[i],argv[i], (char*)0);
			exit(127);
	puts("\n");	

	for (int i = 1; i < argc; i++)
		wait(0);	
}


int main(int argc, char* argv[]) {
	//ex_1();
	//ex_2();
	//ex_3(argc, argv);
	//ex_4(argc, argv);
	ex_5(argc, argv);
	
	return 0;
}
