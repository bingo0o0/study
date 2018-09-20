#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/mman.h>


const char *shm_key = "/demo_shm";

int main()
{
	int fd = shm_open(shm_key, O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	if (fd < 0)
	{
		perror("shm_open failed\n");
		return -1;
	}

	if (ftruncate(fd, 1000) == -1)
	{
		perror("ftruncate failed\n");
		return -1;
	}

	void *addr = mmap(NULL, 1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (!addr)
	{
		perror("mmap failed\n");
		return -1;
	}

	return 0;
}
