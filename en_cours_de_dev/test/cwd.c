#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main()
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("\n\nCurrent working dir: %s\n\n\n", cwd);
	}
	else
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	printf("OK !");
}