#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

void il_catch_CHLD(int);	/* signalo apdorojimo f-ja */
void il_catch_ALRM(int);
void il_child(int parent);		/* vaiko proceso veiksmai */
void il_parent(int pid);	/* tevo proceso veiksmai */

void il_child(int parent) {
	printf("        child: I'm the child\n");
	sleep(3);
	kill(parent, SIGALRM);

	printf("        child: I'm exiting\n");
	exit(123);
}

void il_parent(int pid) {
	printf("parent: I'm the parent\n");
	signal(SIGALRM, il_catch_ALRM);

	sleep(5);
	printf("parent: exiting\n");
}

void il_catch_CHLD(int snum) {
	int pid;
	int status;

	pid = wait(&status);
	printf("parent: child process exited with value %d\n", WEXITSTATUS(status));
}

void il_catch_ALRM(int snum) {
	printf("Got signal: %d\n", snum);
}

int main(int argc, char **argv) {
int pid;

signal(SIGCHLD, il_catch_CHLD);
switch (pid = fork()) {
	case 0:
		il_child(pid);
		break;
	default:
		il_parent(pid);
		break;
	case -1:
		perror("fork");
		exit(1);
	}
	exit(0);
}
