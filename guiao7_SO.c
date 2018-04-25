#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// tee ui | cat
// cat ui
// tee ui | cat | tee ai

int n = 0;
int c = 0;

void f(int i) { // Alarm
	n++;
	alarm(1);
}

void g(int i) {	// CTRL C
	c++;
	printf("%d\n",n);
}

void h(int i) {// CTRL + \""
	printf ("%d\n", c);
	exit(0);
}

int main() {
	signal(SIGALRM, f);
	signal(SIGINT, g);
	signal(SIGQUIT, h);
	alarm(1);
	while(1) {
		pause();	
	}

	printf("Adeus...\n");
	return 0;
}