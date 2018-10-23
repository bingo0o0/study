#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_BUF_SIZE (1024)

static void test_pipe()
{
	int size;
	char buffer[MAX_BUF_SIZE] = {0,};
	int filedes[2] = {0,};
	pid_t pid = 0;
	
	if (pipe(filedes) != 0)
	{
		perror("pipe failed \n");
		return;
	}

	pid = fork();
	if (-1 == pid)
	{
		perror("fork failed");
		return;
	}
	else if (pid == 0)
	{
		//\ child close read fileno
		close(filedes[0]);
		write(filedes[1], "test", 4);
		close(filedes[1]);
		sleep(3);
		_exit(0);
	}
	else
	{
		printf("start to read\n");
		//\ parent; close write fileno
		close(filedes[1]);

		//\ 阻塞读取
		size = read(filedes[0], buffer, sizeof(buffer));
		if (size > 0)
			printf("read : %s\n", buffer);
		else
			perror("read failed");

		wait(NULL);
	}
	return;
}


int main()
{
	test_pipe();


	printf(" end !!!! \n");
	return 0;
}
