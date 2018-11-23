#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MMAP_SIZE_SNOW 6000

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Invalid param\n");
		return -1;
	}

	int fd = -1;
	int size = -1;
	char *addr = NULL;
	struct stat stStat;

	fd = open(argv[1], O_RDWR, 0777);
	if (fd < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return fd;
	}

	if (fstat(fd, &stStat) != 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	size = stStat.st_size;
	printf("file length: %d\n", size);

	addr = mmap(NULL, MMAP_SIZE_SNOW, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (!addr)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		close(fd);
		return -1;
	}

	close(fd);
	printf("mmap success\n");
	//printf("file buff:%s\n", addr);
	
	addr[4096] = 'a';
	addr[8191] = 'b';
	//addr[8193] = 'c';

	munmap(addr, MMAP_SIZE_SNOW);
	return 0;
}













