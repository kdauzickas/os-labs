#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main( int argc, char * argv[] ){
	pid_t pagr, f1;
	char komanda[25];

	pagr = getpid();

	printf("Pagrindinis: %ld\n", (long) pagr);

	f1 = fork();

	if (f1 != 0) {
		sleep(2);

		sprintf(komanda, "ps -ef | grep %ld", (long) pagr);

		system(komanda);
	}

	return 0;
}