#include <stdio.h>
#include <string.h>
#include <errno.h>

const char *testFile = "./test.txt";



int main(int argc, char *argv[])
{
	int err;
	long size;
	FILE *fd = NULL;
	fd = fopen(testFile, "a+");
	if (NULL == fd)
	{
		printf("open file[%s] filed:%s\n", testFile, strerror(errno));
		return -1;	
	}

	err = fseek(fd, 0, SEEK_END);
	if (err != 0)
	{
		printf("fseek failed:%s\n", strerror(err));
		fclose(fd);
		return -1;
	}

	size = ftell(fd);
	if (-1L == size)
	{
		printf("ftell failed:%s\n", strerror(errno));
		fclose(fd);
		return -1;	
	}

	printf("file size:%ld\n", size);

	fclose(fd);
	return 0;
}
