#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main( int argc, char * argv[] ){
	printf("My pid: %ld\n", (long) getpid());

	fork();
	printf("My pid: %ld\n", (long) getpid());

	fork();
	printf("My pid: %ld\n", (long) getpid());

	return 0;
}