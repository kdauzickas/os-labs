#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	if (argc != 2) {
		puts("Priimamas 1 argumentas");
	 	return 1;
	}

	int param = atoi(argv[1]);

	printf("Mano pid: %ld\n", (long) getpid());
	printf("Tevo pid: %ld\n\n", (long) getppid());
	printf("Argumentas: %d\n\n", param);

	sprintf(argv[1], "%d", param-1);

	if (param-1 > 0) {
		execv(argv[0], argv);
	}

	return 0;
}