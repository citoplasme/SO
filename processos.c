#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ids () {
	int p = getppid();
	printf("ID %d\n",getpid()); // process id
	printf("ID pai %d   ",p); // process parent id
	if (p == 1) {
		printf("ORFAO");
	} 
	printf("\n");
}

void ex1 () {
	printf("ID procura %d\n",getpid()); // process id
	printf("ID pai %d\n",getppid() ); // process parent id
	printf("%d\n",fork() ); // fork 0 == filho, maior que 0 é o pai, -1 falhou
	//printf("%d\n",fork() );
	//printf("%d\n",fork() );
	//printf("%d\n",fork() );
}

void ex2() {
  int fork1 = fork(); // criação do filho
  if (fork1 < 0) {
    printf("error\n");
  } else if (fork1 == 0) {
    printf("This is the child\n");
  	ids();
  } else {
    printf("This is the parent\n");
    ids();
    printf("Child: %d\n", fork1);
    }
}

#define MAX_COUNT 10

void ex3 () {
	 pid_t  pid;
     int    i;

     for (i = 1; i <= MAX_COUNT; i++) {
          pid = fork();
          if (!pid) {
          		printf("Filho %d ID %d Pai %d \n",i, getpid(), getppid());
          		_exit(1);	
          }
          int status;
          wait(&status);
          if (WIFEXITED(status))
          	printf("Filho %d fez exit de %d\n",i,WEXITSTATUS(status));
    } 
}

void ex4() {
  pid_t pids[MAX_COUNT];
  for (int i = 0; i < MAX_COUNT; ++i) {
    pid_t pid = fork();
    pids[i] = pid;
    if (!pid) {
      _exit(i+1);
    }
  } 
  for (int i = 0; i < MAX_COUNT; ++i) {
    int status;
    pid_t p = waitpid(pids[i],&status,0);
    if (WIFEXITED(status))
      printf("Filho %d com pid %d terminou com exit de %d\n",i,p, WIFEXITED(status));
  }
}

// gerar filhos de filhos
void child(int i) {
    int pid;

    printf("Child number %d, ID %d Parent %d \n", i,  getpid(), getppid());
    if (i == 10)
        return;
    pid = fork();
    if (pid < 0)
        printf("error\n");
    else if (pid == 0)
        child(++i);
    else
        waitpid(pid, NULL, 0);
    exit(0);
}
void ex5 () {
    int i = 0;  
    int pid = fork();
    if (pid < 0)
        printf("error\n");
    else if (pid == 0)
        child(++i);
    else
        waitpid(pid, NULL, 0);
}


int main () {
	//ex1();
	//ex2();
	//ex3();
	//ex4();
	ex5();
	_exit(0);
	return 0;
}
