#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main( int argc, char * argv[] ){
	printf("Pagrindinis: %ld\n", (long) getpid());

	pid_t f1 = fork();

	if (f1 == 0) {
		sleep(2);
		printf("Vaiko tevas: %ld\n", (long) getppid());
	}

	return 0;
}