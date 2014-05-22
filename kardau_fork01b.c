#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main( int argc, char * argv[] ){
	printf("My pid: %ld\n", (long) getpid());

	pid_t f1 = fork();
	printf("My pid: %ld\n", (long) getpid());

	if (f1 != 0) {
		fork();
		printf("My pid: %ld\n", (long) getpid());
	}

	return 0;
}