#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	int param;
	char naujasParam[10];

	if (argc != 2) {
		puts("Priimamas 1 argumentas");
	 	return 1;
	}

	param = atoi(argv[1]);

	printf("Mano pid: %ld\n", (long) getpid());
	printf("Tevo pid: %ld\n\n", (long) getppid());
	printf("Argumentas: %d\n\n", param);

	sprintf(naujasParam, "%d", param-1);

	if (param-1 > 0) {
		execl(argv[0], argv[0], naujasParam, (char*)NULL);
	}

	return 0;
}
