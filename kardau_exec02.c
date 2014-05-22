#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	FILE *f = fopen("script.sh", "w");
	if (f == NULL) {
	    printf("Error opening file!\n");
	    exit(1);
	}

	const char *script = "ls -la";
	fputs(script, f);
	fclose(f);

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));

	char komanda[1024];
	sprintf(komanda, "sh %s/script.sh", cwd);

	system(komanda);
}