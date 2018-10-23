#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern "C" {
void dumpList();
}

int main()
{
	//int i = 0;
	//void *pAddr = NULL;
	void *ptmp = new int[100];
#if 0	
	printf("==============================pAddr:%p\n", pAddr);
	while(i<20)
	{
		pAddr = malloc(1024);
		printf("malloc 1024 %p\n", pAddr);
		
		if (i%5 == 0)
			free(pAddr);
		
		i++;
	}
#endif
	
	dumpList();
	printf("########################ptmp:%p\n", ptmp);
	sleep(3);
	
	
	return 0;
}
