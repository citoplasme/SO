#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
#include <signal.h>

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
      //printf("Filho %d \n",i );
      _exit(i+1);
    }
  } 
  for (int i = 0; i < MAX_COUNT; ++i) {
    int status;
    pid_t p = waitpid(pids[i],&status,0);
    if (WIFEXITED(status))
      printf("Filho %d com pid %d terminou com exit de %d => Pai %d\n",(i+1),p, WIFEXITED(status), getppid());
  }
}

// gerar filhos de filhos
void child(int i) {
    int pid;

    printf("Child number %d, ID %d Parent %d \n", i,  getpid(), getppid());
    if (i == MAX_COUNT)
        return;
    pid = fork();
    if (pid < 0)
        printf("error\n");
    else if (pid == 0)
        child(++i);
    else
        waitpid(pid, NULL, 0);
    _exit(0);
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
// procura em matriz
void killEmAll (pid_t pids[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    kill(pids[i], SIGUSR1); // kill all the processes and cleans them
  }
}

int ex6 () {
    int result = 0;
    int num,i,j,z;
    int lines = rand() % 100, col = rand() % 100000;
    int pid[lines]; // um filho por linha
    int matriz[lines][col];

    srand((unsigned)time(NULL)); 

    num = rand() % 100;

    for(i = 0; i < lines; i++) {
        for(j = 0; j < col; j++) {
            matriz[i][j] = rand() % 1000; 
            //printf("%i  ",matriz[i][j]);
        }
    }
    //create paralell processes to search in matrix
    for(i = 0; i < lines; i++) {
        pid[i] = fork();
        if (pid[i] == 0) { 
            for(z = 0; z < col; z++) {
                if (matriz[i][z] == num) { 
                  result = 1;
                  printf("TRUE\n");
                  killEmAll(pid, lines);
                }
            }
        _exit(0);
        }       
    }

    return result;
}

void ex7 () {

    int num,i,j,z;
    int lines = rand() % 100, col = rand() % 100000;
    int pid[lines];
    int matriz[lines][col];

    srand((unsigned)time(NULL)); 

    num = rand() % 100;

    for(i = 0; i < lines; i++) {
        for(j = 0; j < col; j++) {
            matriz[i][j] = rand() % 1000; 
            printf("%i  ",matriz[i][j]);
        }
    }

    printf("\n *** Results: *** \n");

    //create paralell processes to search in matrix
    for(i = 0; i < lines; i++) {
        pid[i] = fork();
        if (pid[i] == 0) { 
            for(z = 0; z < col; z++) {
                if (matriz[i][z] == num) { 
                  printf("Found %d in position (%d , %d)\n",num,i,z); 
                }
            }
        _exit(0);
        }       
    }

    for(i = 0; i < lines; i++) {
        wait(NULL);
    }
}

int main () {
	//ex1();
	//ex2();
	//ex3();
	//ex4();
	//ex5();
  	int x = ex6();
  	if (x == 1) printf("TRUE\n");
  	else printf("FALSE\n");
	//ex7();
  	_exit(0);
	return 0;
}
