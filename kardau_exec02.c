#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	FILE *f;
	const char *script;
	char cwd[1024], komanda[1024];

	f = fopen("script.sh", "w");
	if (f == NULL) {
	    printf("Error opening file!\n");
	    exit(1);
	}

	script = "ls -la";
	fputs(script, f);
	fclose(f);

	getcwd(cwd, sizeof(cwd));

	sprintf(komanda, "sh %s/script.sh", cwd);

	system(komanda);
}
