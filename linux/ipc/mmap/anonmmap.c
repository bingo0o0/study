#include "snow.h"


int main()
{
	char *addr;
	pid_t pid;

	addr = mmap(NULL, 1000, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (addr == MAP_FAILED)
	{
		perror("map filaed \n");
		return -1;
	}

	const char *txt = "this is anonynmous mmap";
	memcpy(addr, txt, strlen(txt));

	pid = fork();
	if (pid == 0)
	{
		// child
		printf("child txt:%s \n", txt);
		txt = "child xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
		memcpy(addr, txt, strlen(txt));

		printf("child end\n");
		munmap(addr, 1000);
		exit(0);
	}

	sleep(3);

	printf("farent txt:%s", addr);

	printf("farent end\n");

	munmap(addr, 1000);

	return 0;
}
