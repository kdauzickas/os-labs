#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main( int argc, char * argv[] ){
	pid_t pagr = getpid();

	printf("Pagrindinis: %ld\n", (long) pagr);

	pid_t f1 = fork();

	if (f1 != 0) {
		sleep(2);
		char komanda[25];

		sprintf(komanda, "ps -ef | grep %ld", (long) pagr);

		system(komanda);
	}

	return 0;
}